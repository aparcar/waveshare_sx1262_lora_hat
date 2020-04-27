#include "sx126x_lora_hat.h"

/******************************************************************************
				sx126x mode :	default mode
					 parameter:
				address_high:	default 0x00
				 address_low:	default 0x00
							net_id: default 0x00
							serial:	default 0x62
							 power: default 0x00
						 channel: default 0x17
	 transmission_mode: default 0x03
					crypt_high: default 0x00
					 crypt_low: default 0x00
******************************************************************************/
lora_para_t default_mode = {
	.address_high = 			DEFAULE_ADDH_VALUE,
	.address_low = 				DEFAULE_ADDL_VALUE,
	.net_id = 						DEFAULT_NETID_VALUE,
	.serial = 						DEFAULE_SERIAL_VALUE,
	.power = 							DEFAULT_POWER_VALUE,
	.channel = 						DEFAULT_CHANNEL_VALUE,
	.transmission_mode = 	DEFAULT_TRANSIMISSION_VALUE,
	.crypt_high = 				DEFAULT_CRYPTH_VALUE,
	.crypt_low = 					DEFAULT_CRYPTL_VALUE
};

/******************************************************************************
			sx126x mode :	broadcast & monitor mode
				 parameter:
			address_high:	0xff
			 address_low:	0xff
						net_id: 0x00
						serial:	0x62
						 power: 0x00
					 channel: 0x17
 transmission_mode: 0x03
				crypt_high: 0x00
				 crypt_low: 0x00
******************************************************************************/
lora_para_t transparent_mode = {
	.address_high = 			BROADCAST_ADDH_VALUE,
	.address_low = 				BROADCAST_ADDL_VALUE,
	.net_id = 						BROADCAST_NETID_VALUE,
	.serial = 						BROADCAST_SERIAL_VALUE,
	.power = 							BROADCAST_POWER_VALUE,
	.channel = 						BROADCAST_CHANNEL_VALUE,
	.transmission_mode = 	BROADCAST_TRANSIMISSION_VALUE,
	.crypt_high = 				BROADCAST_CRYPTH_VALUE,
	.crypt_low = 					BROADCAST_CRYPTL_VALUE
};

/******************************************************************************
			sx126x mode :	wor send mode
				 parameter:
			address_high:	0x00
			 address_low:	0x00
						net_id: 0x00
						serial:	0x62
						 power: 0x00
					 channel: 0x17
 transmission_mode: 0x0b
				crypt_high: 0x00
				 crypt_low: 0x00
******************************************************************************/
lora_para_t wor_mode = {
	.address_high = 			WOR_ADDH_VALUE,
	.address_low = 				WOR_ADDL_VALUE,
	.net_id = 						WOR_NETID_VALUE,
	.serial = 						WOR_SERIAL_VALUE,
	.power = 							WOR_POWER_VALUE,
	.channel = 						WOR_CHANNEL_VALUE,
	.transmission_mode = 	WOR_TRANSIMISSION_VALUE,
	.crypt_high = 				WOR_CRYPTH_VALUE,
	.crypt_low = 					WOR_CRYPTL_VALUE
};

/******************************************************************************
				sx126x mode :	relay mode
					 parameter:
				address_high:	0x00
				 address_low:	0x00
							net_id: 0x00
							serial:	0x62
							 power: 0x00
						 channel: 0x17
	 transmission_mode: 0x03
					crypt_high: 0x00
					 crypt_low: 0x00
******************************************************************************/
lora_para_t relay_mode = {
	.address_high = 			RELAY_ADDH_VALUE,
	.address_low = 				RELAY_ADDL_VALUE,
	.net_id = 						RELAY_NETID_VALUE,
	.serial = 						RELAY_SERIAL_VALUE,
	.power = 							RELAY_POWER_VALUE,
	.channel = 						RELAY_CHANNEL_VALUE,
	.transmission_mode = 	RELAY_TRANSIMISSION_VALUE,
	.crypt_high = 				RELAY_CRYPTH_VALUE,
	.crypt_low = 					RELAY_CRYPTL_VALUE
};

void cfg_sx126x_io(uint8_t status)
{
	if(CFG_REGISTER == status){
	  M0_RESET();
	  M1_SET();
		HAL_Delay(5);
	}else if(NORMAL_STATUS == status){
		M0_RESET();
		M1_RESET();
		HAL_Delay(5);
	}else if(WOR_STATUS == status){
		M0_SET();
		M1_RESET();
		HAL_Delay(5);
	}else if(SLEEP_STATUS == status){
		M0_SET();
		M1_SET();
		HAL_Delay(5);
	}
}
	
uint8_t cfg_sx126x_mode(uint8_t mode)
{
	uint8_t flag = ERROR;
	if(TRANSPARENT_MODE == mode){
		cfg_sx126x_io(CFG_REGISTER);
		flag = sx126x_write_register(transparent_mode);
		if(SUCCESS == flag){
			cfg_sx126x_io(NORMAL_STATUS);
			return SUCCESS;
		}else{
			return ERROR;
		}
	}else if(RELAY_MODE == mode){
		cfg_sx126x_io(CFG_REGISTER);
		if(SUCCESS == sx126x_write_register(relay_mode)){
			cfg_sx126x_io(NORMAL_STATUS);
			return SUCCESS;
		}else{
			return ERROR;
		}
	}else if(WOR_TRANSMISSION_MODE == mode){
		cfg_sx126x_io(CFG_REGISTER);
		if(SUCCESS == sx126x_write_register(wor_mode)){
			cfg_sx126x_io(WOR_STATUS);
			return SUCCESS;
		}else{
			return ERROR;
		}
	}else{
		return ERROR;
	}
}

extern UART_HandleTypeDef huart1;
extern uint8_t buffer[MAX_BYTES];
extern uint8_t init_cplt_flag;

uint8_t sx126x_write_register(lora_para_t para)
{
	int8_t i;
	buffer[0] = CFG_HEADER;
	buffer[1] = REG_START;
	buffer[2] = REG_NUMBER;
	
	for(i=3;i<12;i++){
		buffer[i] = *(&para.address_high + i - 3);
	}
	HAL_UART_Transmit_IT(&huart1,(uint8_t *)buffer,12);
	HAL_UART_Receive_IT(&huart1,(uint8_t *)buffer,12);
	HAL_Delay(500);
	if(CFG_RETURN == buffer[0]){
		buffer[0] = 0;
		init_cplt_flag = SUCCESS;
		return SUCCESS;
	}
	return ERROR;
}

uint8_t sx126x_send(int8_t *send_data)
{
	HAL_UART_Transmit_IT(&huart1,(uint8_t *)send_data,strlen((const char *)send_data));
	return SUCCESS;
}

