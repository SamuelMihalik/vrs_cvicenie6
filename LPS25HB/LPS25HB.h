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

#define LPS25HB_ADDRESS_PRESS_OUT_XL		0x28
#define LPS25HB_ADDRESS_PRESS_OUT_L			0x29
#define LPS25HB_ADDRESS_PRESS_OUT_H			0x2A

#define LPS25HB_ADDRESS_TEMP_OUT_L			0x2B
#define LPS25HB_ADDRESS_TEMP_OUT_H			0x2C






uint8_t LPS25HB_read_byte(uint8_t register_address);
void LPS25HB_read_array(uint8_t register_address, uint8_t* data, uint8_t size);
void LPS25HB_write_byte(uint8_t register_address, uint8_t data);

uint8_t LPS25HB_Init(I2C_ReadCallback read_callback,
					 I2C_WriteCallback write_callback);

float LPS25HB_get_pressure(void);
float LPS25HB_get_temperature(void);











#endif /* LPS25HB_H_ */
