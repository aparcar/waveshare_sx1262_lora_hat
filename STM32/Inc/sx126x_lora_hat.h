#ifndef __SX126X_LORA_HAT_H
#define __SX126X_LORA_HAT_H

#include "stm32f1xx.h"
#include "main.h"
#include <string.h>

#define CFG_REGISTER												0x01
#define NORMAL_STATUS												0x02
#define WOR_STATUS													0x03
#define SLEEP_STATUS												0x04

#define TRANSPARENT_MODE										0x02
#define RELAY_MODE													0x03
#define WOR_TRANSMISSION_MODE								0x04

#define MAX_BYTES														1000

#define CFG_HEADER													0xC2
#define CFG_RETURN													0xC1
#define REG_START														0x00
#define REG_NUMBER													0x09

/********************DEAFULE REGISTER VALUE********************/
#define DEFAULE_ADDH_VALUE									0x00
#define DEFAULE_ADDL_VALUE									0x00
#define DEFAULT_NETID_VALUE									0x00
#define DEFAULE_SERIAL_VALUE								0x62
#define DEFAULT_POWER_VALUE									0x00
#define DEFAULT_CHANNEL_VALUE								0x17
#define DEFAULT_TRANSIMISSION_VALUE					0x03
#define DEFAULT_CRYPTH_VALUE								0x00
#define DEFAULT_CRYPTL_VALUE								0x00

#define TRANSPARENT_BROADCAST

/********************BROADCAST AND MONITOR REGISTER VALUE********************/
#ifdef 	TRANSPARENT_BROADCAST
#define BROADCAST_ADDH_VALUE								0xFF
#define BROADCAST_ADDL_VALUE 								0xFF
#elif defined TRANSPARENT_P2P
#define BROADCAST_ADDH_VALUE								0x00
#define BROADCAST_ADDL_VALUE								0x00
#endif
#define BROADCAST_NETID_VALUE								0x00
#define BROADCAST_SERIAL_VALUE							0x62
#define BROADCAST_POWER_VALUE								0x00
#define BROADCAST_CHANNEL_VALUE							0x17
#define BROADCAST_TRANSIMISSION_VALUE				0x03
#define BROADCAST_CRYPTH_VALUE							0x00
#define BROADCAST_CRYPTL_VALUE							0x00

/********************RELAY REGISTER VALUE********************/
#define RELAY_ADDH_VALUE										0x00
#define RELAY_ADDL_VALUE 										0x00
#define RELAY_NETID_VALUE										0x01
#define RELAY_SERIAL_VALUE									0x62
#define RELAY_POWER_VALUE										0x00
#define RELAY_CHANNEL_VALUE									0x17
#define RELAY_TRANSIMISSION_VALUE						0x03
#define RELAY_CRYPTH_VALUE									0x00
#define RELAY_CRYPTL_VALUE									0x00

/********************WOR REGISTER VALUE********************/
#define WOR_ADDH_VALUE											0x00
#define WOR_ADDL_VALUE 											0x00
#define WOR_NETID_VALUE											0x00
#define WOR_SERIAL_VALUE										0x62
#define WOR_POWER_VALUE											0x00
#define WOR_CHANNEL_VALUE										0x17
#define WOR_TRANSIMISSION_VALUE							0x0b
#define WOR_CRYPTH_VALUE										0x00
#define WOR_CRYPTL_VALUE										0x00

#define M0_PIN					GPIO_PIN_14
#define M1_PIN					GPIO_PIN_15

#define M0_GPIO					GPIOB
#define M1_GPIO					GPIOB

#define M0_SET()				HAL_GPIO_WritePin(M0_GPIO,M0_PIN,GPIO_PIN_SET)
#define M0_RESET()			HAL_GPIO_WritePin(M0_GPIO,M0_PIN,GPIO_PIN_RESET)

#define M1_SET()				HAL_GPIO_WritePin(M1_GPIO,M1_PIN,GPIO_PIN_SET)
#define M1_RESET()			HAL_GPIO_WritePin(M1_GPIO,M1_PIN,GPIO_PIN_RESET)

#define LED1_ON() 			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET)
#define LED1_OFF()			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET)

typedef struct lora_para_t{
	uint8_t address_high;
	uint8_t address_low;
	uint8_t net_id;
	uint8_t serial;
	uint8_t power;
	uint8_t channel;
	uint8_t transmission_mode;
	uint8_t crypt_high;
	uint8_t crypt_low;
}lora_para_t;

extern lora_para_t default_mode;
extern lora_para_t transparent_mode;
extern lora_para_t wor_mode;
extern lora_para_t relay_mode;

void cfg_sx126x_io(uint8_t status);
uint8_t cfg_sx126x_mode(uint8_t mode);
uint8_t sx126x_write_register(lora_para_t send_data);
uint8_t sx126x_send(int8_t *send_data);

#endif

