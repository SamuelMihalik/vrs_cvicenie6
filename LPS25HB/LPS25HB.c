#include "LPS25HB.h"

uint8_t lps25hb_address = LPS25HB_DEVICE_ADDRESS_0;

typedef void (*I2C_ReadCallback)(uint8_t slave_address,
                                 uint8_t register_address,
                                 uint8_t* data,
                                 uint8_t size);

typedef void (*I2C_WriteCallback)(uint8_t slave_address,
                                  uint8_t register_address,
                                  uint8_t* data,
                                  uint8_t size);

static I2C_ReadCallback I2C_read_data = NULL;
static I2C_WriteCallback I2C_write_data = NULL;

uint8_t LPS25HB_read_byte(uint8_t register_address) {
	if (I2C_read_data == NULL) {
		return 0;
	}

	uint8_t rx_data;
	I2C_read_data(lps25hb_address, register_address, &rx_data, 1);
	return rx_data;
}

void LPS25HB_read_array(uint8_t register_address, uint8_t* data, uint8_t size) {
	if (I2C_read_data == NULL || data == NULL || size == 0) {
	        return;
	}

	I2C_read_data(lps25hb_address, register_address, data, size);
}

void LPS25HB_write_byte(uint8_t register_address, uint8_t data) {
	if (I2C_write_data == NULL) {
	        return;
	}

	I2C_write_data(lps25hb_address, register_address, &data, 1);
}

uint8_t LPS25HB_Init(I2C_ReadCallback read_callback,
					 I2C_WriteCallback write_callback) {

	if(read_callback != NULL)
		I2C_read_data = read_callback;

	if(write_callback != NULL)
		I2C_write_data = write_callback;

	uint8_t status = 1;

	LL_mDelay(100);

	uint8_t who_am_i = LPS25HB_read_byte(LPS25HB_WHO_AM_I_ADDRESS);

	if (who_am_i != LPS25HB_WHO_AM_I_VALUE) {
		lps25hb_address = LPS25HB_DEVICE_ADDRESS_1;
		who_am_i = LPS25HB_read_byte(LPS25HB_WHO_AM_I_ADDRESS);

		if (who_am_i != LPS25HB_WHO_AM_I_VALUE) {
			status = 0;
			return status;
		}
	}

	uint8_t ctrl1 = LPS25HB_read_byte(LPS25HB_ADDRESS_CTRL1);
	ctrl1 &= 0xF;
	ctrl1 |= 0x90;

	LPS25HB_write_byte(LPS25HB_ADDRESS_CTRL1, ctrl1);

	initial_pressure = LPS25HB_get_pressure();

	return status;
}

float LPS25HB_get_pressure(void) {

	if (I2C_read_data == NULL) {
	        return -1;
	}

	uint8_t pressure_data[3];

	LPS25HB_read_array(LPS25HB_ADDRESS_PRESS_OUT_XL, pressure_data, 3);

	int32_t pressure_raw = (int32_t)(pressure_data[2] << 16 |
									 pressure_data[1] << 8 |
									 pressure_data[0]);

	return (float)(pressure_raw / 4096.0f);
}

float LPS25HB_get_temperature(void) {

	if (I2C_read_data == NULL) {
		return -1;
	}

	uint8_t temperature_data[2];

	LPS25HB_read_array(LPS25HB_ADDRESS_TEMP_OUT_L, temperature_data, 2);

	int16_t temperature_raw = (int16_t)(temperature_data[1] << 8 |
							   	   	    temperature_data[0]);

	return 42.5f + ((float)temperature_raw / 480.0f);
}





