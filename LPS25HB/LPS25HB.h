/*
 * LPS25HB.h
 *
 *  Created on: Oct 28, 2024
 *      Author: mihal
 */

#ifndef LPS25HB_H_
#define LPS25HB_H_

#include "i2c.h"

#define LPS25HB_DEVICE_ADDRESS_0			0xB9
#define LPS25HB_DEVICE_ADDRESS_1			0xBB

#define LPS25HB_WHO_AM_I_VALUE				0xBD
#define LPS25HB_WHO_AM_I_ADDRESS			0x0F

#define LPS25HB_ADDRESS_CTRL1				0x20


uint8_t LPS25HB_read_byte(uint8_t register_address);
void LPS25HB_read_array(uint8_t register_address, uint8_t* data, uint8_t size);
void LPS25HB_write_byte(uint8_t register_address, uint8_t data);

uint8_t LPS25HB_Init(void (*read_callback)(uint8_t slave_address, uint8_t register_address, uint8_t* data, uint8_t size),
					void (*write_callback)(uint8_t slave_address, uint8_t register_address, uint8_t* data, uint8_t size));











#endif /* LPS25HB_H_ */
