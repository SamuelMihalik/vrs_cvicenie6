#ifndef HTS221_H_
#define HTS221_H_

#include "i2c.h"

#define HTS221_DEVICE_ADDRESS_0				0xBF

#define HTS221_WHO_AM_I_VALUE				0xBC
#define HTS221_WHO_AM_I_ADDRESS				0x0F

#define HTS221_ADDRESS_CTRL1				0x20

#define HTS221_ADDRESS_HUMIDITY_L			0x28
#define HTS221_ADDRESS_HUMIDITY_H			0x29

#define HTS221_ADDRESS_H0_rH_x2				0x30
#define HTS221_ADDRESS_H1_rH_x2				0x31

#define HTS221_ADDRESS_H0_T0_OUT_L			0x36
#define HTS221_ADDRESS_H0_T0_OUT_H			0x37

#define HTS221_ADDRESS_H1_T0_OUT_L			0x3A
#define HTS221_ADDRESS_H1_T0_OUT_H			0x3B






typedef void (*I2C_ReadCallback)(uint8_t slave_address,
                                 uint8_t register_address,
                                 uint8_t* data,
                                 uint8_t size);

typedef void (*I2C_WriteCallback)(uint8_t slave_address,
                                  uint8_t register_address,
                                  uint8_t* data,
                                  uint8_t size);

uint8_t HTS221_read_byte(uint8_t register_address);
void HTS221_read_array(uint8_t register_address, uint8_t* data, uint8_t size);
void HTS221_write_byte(uint8_t register_address, uint8_t data);

uint8_t HTS221_Init(I2C_ReadCallback read_callback,
					I2C_WriteCallback write_callback);

#endif
