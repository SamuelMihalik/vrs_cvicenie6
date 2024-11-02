/*
 * LPS25HB.c
 *
 *  Created on: Oct 28, 2024
 *      Author: mihal
 */

#include "LPS25HB.h"

uint8_t address = LPS25HB_DEVICE_ADDRESS_0;

static void (* I2C_read_data)(uint8_t slave_address, uint8_t register_address, uint8_t* data, uint8_t size) = 0;
static void (* I2C_write_data)(uint8_t slave_address, uint8_t register_address, uint8_t* data, uint8_t size) = 0;

uint8_t LPS25HB_read_byte(uint8_t register_address) {
		uint8_t rx_data;
	    I2C_read_data(address, register_address, &rx_data, 1);
	    return rx_data;
}

void LPS25HB_read_array(uint8_t register_address, uint8_t* data, uint8_t size) {
		for(uint8_t i=0; i<size; i++){
			I2C_read_data(address, register_address+i, data+i, 1);
		}
}

void LPS25HB_write_byte(uint8_t register_address, uint8_t data)
{
	I2C_write_data(address, register_address, data, 1);
}

uint8_t LPS25HB_Init(void (*read_callback)(uint8_t slave_address, uint8_t register_address, uint8_t* data, uint8_t size),
					void (*write_callback)(uint8_t slave_address, uint8_t register_address, uint8_t* data, uint8_t size)) {


	if(read_callback != 0)
		I2C_read_data = read_callback;

	if(write_callback != 0)
		I2C_write_data = write_callback;


	uint8_t status = 1;

	LL_mDelay(100);

	uint8_t address_value = LPS25HB_read_byte(address);

	if (address_value != LPS25HB_WHO_AM_I_VALUE) {
		address = LPS25HB_DEVICE_ADDRESS_1;
		address_value = LPS25HB_read_byte(address);

		if (address_value != LPS25HB_WHO_AM_I_VALUE) {
			status = 0;
			return status;
		}
	}

	uint8_t ctrl1 = LPS25HB_read_byte(LPS25HB_ADDRESS_CTRL1);
	ctrl1 &= 0xF;
	ctrl1 |= 0x90;

	LPS25HB_write_byte(LPS25HB_ADDRESS_CTRL1, ctrl1);

	return status;
}
