#!/usr/bin/python
# -*- coding: UTF-8 -*-

import RPi.GPIO as GPIO
import serial
import time
import sys
	
M0 = 22
M1 = 27

CFG_REG = [b'\xC2\x00\x09\x00\x00\x00\x62\x00\x17\x0b\x00\x00']
RET_REG = [b'\xC1\x00\x09\x00\x00\x00\x62\x00\x17\x0b\x00\x00']
r_buff = ""
delay_temp = 1

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
		if ser.isOpen() :
			print("It's setting WOR TRANSMISSION mode")
			ser.write(CFG_REG[0])
		while True :
			if ser.inWaiting() > 0 :
				time.sleep(0.1)
				r_buff = ser.read(ser.inWaiting())
				if r_buff == RET_REG[0] :
					print("WOR TRANSMISSION mode was actived")
					GPIO.output(M0,GPIO.HIGH)
					GPIO.output(M1,GPIO.LOW)
					time.sleep(0.01)
					r_buff = ""
			delay_temp += 1
			if delay_temp > 400000 :
                                print('send wor message')
                                ser.write("This is a WOR TRANSMISSION message\r\n".encode())
                                delay_temp = 0
except :
	if ser.isOpen() :
		ser.close()
	GPIO.cleanup()
