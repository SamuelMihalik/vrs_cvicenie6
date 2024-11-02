#include "HTS221.h"

uint8_t address = HTS221_DEVICE_ADDRESS_0;



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

uint8_t HTS221_read_byte(uint8_t register_address) {
	if (I2C_read_data == NULL) {
		return 0;
	}

	uint8_t rx_data;
	I2C_read_data(address, register_address, &rx_data, 1);
	return rx_data;
}

void HTS221_read_array(uint8_t register_address, uint8_t* data, uint8_t size) {
	if (I2C_read_data == NULL || data == NULL || size == 0) {
	        return;
	}

	I2C_read_data(address, register_address, data, size);
}

void HTS221_write_byte(uint8_t register_address, uint8_t data) {
	if (I2C_write_data == NULL) {
	        return;
	}

	I2C_write_data(address, register_address, &data, 1);
}

uint8_t HTS221_Init(I2C_ReadCallback read_callback,
					 I2C_WriteCallback write_callback) {

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

int8_t HTS221_get_humidity(void) {

	if (I2C_read_data == NULL) {
	        return -1;
	}

	uint8_t humidity_data[2];

	HTS221_read_array(HTS221_ADDRESS_HUMIDITY_OUT_L, humidity_data, 2);

	int16_t humidity_raw = (humidity_data[1] << 8 |
							humidity_data[0]);

	uint8_t x0[2], x1[2], y[2];

	HTS221_read_array(HTS221_ADDRESS_H0_T0_OUT_L, x0, 2);
	HTS221_read_array(HTS221_ADDRESS_H1_T0_OUT_L, x1, 2);
	HTS221_read_array(HTS221_ADDRESS_H0_rH_x2, y, 2);

	int16_t calibration_x0 = (int16_t)(x0[1] << 8 |
									   x0[0]);
	int16_t calibration_x1 = (int16_t)(x1[1] << 8 |
									   x1[0]);

	int8_t calibration_y0 = y[0] / 2;
	int8_t calibration_y1 = y[1] / 2;


	float k = (float)((calibration_y1 - calibration_y0)/(calibration_x1 - calibration_x0));

	float q = (float)(calibration_y1 - k*calibration_x1);

	return (int8_t)(k * humidity_raw + q);
}

int8_t HTS221_get_temeperature(void) {

	if (I2C_read_data == NULL) {
	        return -1;
	}

	uint8_t temperature_data[2];

	HTS221_read_array(HTS221_ADDRESS_TEMP_OUT_L, temperature_data, 2);

	int16_t temperature_raw = (temperature_data[1] << 8 |
							   temperature_data[0]);

	uint8_t x0[2], x1[2], y[2];
	uint8_t t0_t1_msb;

	HTS221_read_array(HTS221_ADDRESS_T0_OUT_L, x0, 2);
	HTS221_read_array(HTS221_ADDRESS_T1_OUT_L, x1, 2);
	HTS221_read_array(HTS221_ADDRESS_T0_degC_x8, y, 2);
	HTS221_read_byte(HTS221_ADDRESS_T1_T2_msb, &t0_t1_msb, 1);

	int16_t calibration_x0 = (int16_t)(x0[1] << 8 |
									   x0[0]);
	int16_t calibration_x1 = (int16_t)(x1[1] << 8 |
									   x1[0]);

	uint16_t t0_degC = y[0];
	uint16_t t1_degC = y[1];

	t0_degC |= ((t0_t1_msb & 0x03) << 8);
	t1_degC |= ((t0_t1_msb & 0x0C) << 6);

	int8_t calibration_y0 = t0_degC / 8;
	int8_t calibration_y1 = t1_degC / 8;



	float k = (float)((y[1] - y[0])/(calibration_x1 - calibration_x0));

	float q = (float)(y[1] - k*calibration_x1);

	return (int8_t)(k * temperature_raw + q);
}




