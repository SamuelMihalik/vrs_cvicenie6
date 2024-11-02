/*
 * HTS221.c
 *
 *  Created on: Oct 28, 2024
 *      Author: mihal
 */

#include "HTS221.h"

static void (* I2C_read_data)(uint8_t slave_address, uint8_t register_address, uint8_t* data, uint8_t size) = 0;
static void (* I2C_write_data)(uint8_t slave_address, uint8_t register_address, uint8_t* data, uint8_t size) = 0;

uint8_t HTS221_read_byte(uint8_t register_address) {
		uint8_t rx_data;
	    I2C_read_data(HTS221_DEVICE_ADDRESS_0, register_address, &rx_data, 1);
	    return rx_data;
}

void HTS221_read_array(uint8_t register_address, uint8_t* data, uint8_t size) {
		for(uint8_t i=0; i<size; i++){
			I2C_read_data(HTS221_DEVICE_ADDRESS_0, register_address+i, data+i, 1);
		}
}

void HTS221_write_byte(uint8_t register_address, uint8_t data)
{
	I2C_write_data(HTS221_DEVICE_ADDRESS_0, register_address, data, 1);
}

uint8_t HTS221_Init(void (*read_callback)(uint8_t slave_address, uint8_t register_address, uint8_t* data, uint8_t size),
					void (*write_callback)(uint8_t slave_address, uint8_t register_address, uint8_t* data, uint8_t size)) {


	if(read_callback != 0)
		I2C_read_data = read_callback;

	if(write_callback != 0)
		I2C_write_data = write_callback;


	uint8_t status = 1;

	LL_mDelay(100);

	uint8_t address_value = HTS221_read_byte(HTS221_DEVICE_ADDRESS_0);

	if (address_value != HTS221_WHO_AM_I_VALUE) {
		status = 0;
		return status;
	}

	uint8_t ctrl1 = HTS221_read_byte(HTS221_ADDRESS_CTRL1);
	ctrl1 &= 0x7C;
	ctrl1 |= 0x83;

	HTS221_write_byte(HTS221_ADDRESS_CTRL1, ctrl1);

	return status;
}


