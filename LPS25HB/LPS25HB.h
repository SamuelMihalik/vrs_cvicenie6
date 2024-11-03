#ifndef LPS25HB_H_
#define LPS25HB_H_

#include "i2c.h"

#define LPS25HB_DEVICE_ADDRESS_0			0xBAU
#define LPS25HB_DEVICE_ADDRESS_1			0xBBU

#define LPS25HB_WHO_AM_I_VALUE				0xBDU
#define LPS25HB_WHO_AM_I_ADDRESS			0x0FU

#define LPS25HB_ADDRESS_CTRL1				0x20U

#define LPS25HB_ADDRESS_PRESS_OUT_XL		0x28U
#define LPS25HB_ADDRESS_PRESS_OUT_L			0x29U
#define LPS25HB_ADDRESS_PRESS_OUT_H			0x2AU

#define LPS25HB_ADDRESS_TEMP_OUT_L			0x2BU
#define LPS25HB_ADDRESS_TEMP_OUT_H			0x2CU

typedef void (*I2C_ReadCallback)(uint8_t slave_address,
                                 uint8_t register_address,
                                 uint8_t* data,
                                 uint8_t size);

typedef void (*I2C_WriteCallback)(uint8_t slave_address,
                                  uint8_t register_address,
                                  uint8_t* data,
                                  uint8_t size);

uint8_t LPS25HB_read_byte(uint8_t register_address);
void LPS25HB_read_array(uint8_t register_address, uint8_t* data, uint8_t size);
void LPS25HB_write_byte(uint8_t register_address, uint8_t data);

uint8_t LPS25HB_Init(I2C_ReadCallback read_callback,
					 I2C_WriteCallback write_callback);

float LPS25HB_get_pressure(void);
float LPS25HB_get_temperature(void);
float LPS25HB_get_height(void);

#endif
