/*
 * HTS221.h
 *
 *  Created on: Oct 28, 2024
 *      Author: mihal
 */

#ifndef HTS221_H_
#define HTS221_H_

#include "i2c.h"

#define HTS221_DEVICE_ADDRESS_0				0xBF

#define HTS221_WHO_AM_I_VALUE				0xBC
#define HTS221_WHO_AM_I_ADDRESS				0x0F

#define HTS221_ADDRESS_CTRL1				0x20

#define HTS221_ADDRESS_HUMIDITY_L			0x28
#define HTS221_ADDRESS_HUMIDITY_H			0x29

uint8_t HTS221_Init();


uint8_t HTS221_read(uint8_t register_address);
void HTS221_write_byte(uint8_t register_address, uint8_t value);
void HTS221_read_callback(void *callback);

uint8_t HTS221_read_byte(uint8_t register_address);
void HTS221_read_array(uint8_t register_address, uint8_t* data, uint8_t size);
void HTS221_write_byte(uint8_t register_address, uint8_t data);

uint8_t HTS221_Init(void (*read_callback)(uint8_t slave_address, uint8_t register_address, uint8_t* data, uint8_t size),
					void (*write_callback)(uint8_t slave_address, uint8_t register_address, uint8_t* data, uint8_t size));








#endif /* HTS221_H_ */
