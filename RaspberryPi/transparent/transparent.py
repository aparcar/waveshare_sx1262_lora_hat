#!/usr/bin/python
# -*- coding: UTF-8 -*-

import RPi.GPIO as GPIO
import serial
import time
import sys
	
M0 = 22
M1 = 27
MODE = ["BROADCAST_AND_MONITOR","P2P"]

CFG_REG = [b'\xC2\x00\x09\xFF\xFF\x00\x62\x00\x17\x03\x00\x00',
		   b'\xC2\x00\x09\x00\x00\x00\x62\x00\x17\x03\x00\x00']
RET_REG = [b'\xC1\x00\x09\xFF\xFF\x00\x62\x00\x17\x03\x00\x00',
		   b'\xC1\x00\x09\x00\x00\x00\x62\x00\x17\x03\x00\x00']
r_buff = ""
delay_temp = 1

if len(sys.argv) != 2 :
	print("there's too much or less arguments,please input again!!!")
	sys.exit(0)
elif (str(sys.argv[1]) == MODE[0]) or (str(sys.argv[1]) == MODE[1]) :
	time.sleep(0.001)
else :
	print("parameters is error")
	sys.exit(0)
	
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(M0,GPIO.OUT)
GPIO.setup(M1,GPIO.OUT)

GPIO.output(M0,GPIO.LOW)
GPIO.output(M1,GPIO.HIGH)
time.sleep(1)

ser = serial.Serial("/dev/ttyS0",9600)
ser.flushInput()
try :
	if str(sys.argv[1]) == MODE[0] :
		if ser.isOpen() :
			print("It's setting BROADCAST and MONITOR mode")
			ser.write(CFG_REG[0])
		while True :
			if ser.inWaiting() > 0 :
				time.sleep(0.1)
				r_buff = ser.read(ser.inWaiting())
				if r_buff == RET_REG[0] :
					print("BROADCAST and MONITOR mode was actived")
					GPIO.output(M1,GPIO.LOW)
					time.sleep(0.01)
					r_buff = ""
				if r_buff != "" :
					print("monitor message:")
					print(r_buff)
					r_buff = ""
			delay_temp += 1
			if delay_temp > 400000 :
                                print('send broadcast message')
                                ser.write("This is a BROADCAST message\r\n".encode())
                                delay_temp = 0
	elif str(sys.argv[1]) == MODE [1]:
		if ser.isOpen() :
			print("It's setting P2P mode")
			ser.write(CFG_REG[1])
		while True :
			if ser.inWaiting() > 0 :
				time.sleep(0.1)
				r_buff = ser.read(ser.inWaiting())
				if r_buff == RET_REG[1] :
					print("P2P mode was actived")
					GPIO.output(M1,GPIO.LOW)
					time.sleep(0.01)
					r_buff = ""
				if r_buff != "" :
					print("receive a P2P message:")
					print(r_buff)
					r_buff = ""
			delay_temp += 1
			if delay_temp > 200000 :
                                print('send p2p message')
                                ser.write("This is a P2P message\r\n".encode())
                                delay_temp = 0
except :
	if ser.isOpen() :
		ser.close()
	GPIO.cleanup()
