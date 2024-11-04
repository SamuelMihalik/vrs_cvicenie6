#include "HTS221.h"

static uint8_t hts221_address = HTS221_DEVICE_ADDRESS_0;

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
	I2C_read_data(hts221_address, register_address, &rx_data, 1);
	return rx_data;
}

void HTS221_read_array(uint8_t register_address, uint8_t* data, uint8_t size) {
	if (I2C_read_data == NULL || data == NULL || size == 0) {
	        return;
	}

	I2C_read_data(hts221_address, register_address, data, size);
}

void HTS221_write_byte(uint8_t register_address, uint8_t data) {
	if (I2C_write_data == NULL) {
	        return;
	}

	I2C_write_data(hts221_address, register_address, &data, 1);
}

uint8_t HTS221_Init(I2C_ReadCallback read_callback, I2C_WriteCallback write_callback) {
	if(read_callback == NULL || write_callback == NULL) {
		return 0;
	}

	I2C_read_data = read_callback;
	I2C_write_data = write_callback;

	LL_mDelay(100);

	uint8_t who_am_i = HTS221_read_byte(HTS221_WHO_AM_I_ADDRESS);
	if (who_am_i != HTS221_WHO_AM_I_VALUE) {
		return 0;
	}

	uint8_t ctrl1 = HTS221_read_byte(HTS221_ADDRESS_CTRL1);
	ctrl1 &= 0x7C;
	ctrl1 |= 0x83;

	HTS221_write_byte(HTS221_ADDRESS_CTRL1, ctrl1);

	return 1;
}


int8_t HTS221_get_humidity(void) {

    if (I2C_read_data == NULL) {
        return -1;
    }

    uint8_t humidity_data[2];
    HTS221_read_array(HTS221_ADDRESS_HUMIDITY_OUT_L, humidity_data, 2);
    int16_t humidity_raw = (humidity_data[1] << 8) | humidity_data[0];

    uint8_t h_rh_x2[2];
    uint8_t h0_t0_out[2], h1_t0_out[2];

    HTS221_read_array(HTS221_ADDRESS_H0_rH_x2, h_rh_x2, 2);
    HTS221_read_array(HTS221_ADDRESS_H0_T0_OUT_L, h0_t0_out, 2);
    HTS221_read_array(HTS221_ADDRESS_H1_T0_OUT_L, h1_t0_out, 2);

    int8_t h0_rh = h_rh_x2[0] / 2;
    int8_t h1_rh = h_rh_x2[1] / 2;

    int16_t h0_t0_out_ = (h0_t0_out[1] << 8 | h0_t0_out[0]);
    int16_t h1_t0_out_ = (h1_t0_out[1] << 8 | h1_t0_out[0]);

    int8_t humidity = ((h1_rh - h0_rh) * (humidity_raw - h0_t0_out_) / (h1_t0_out_ - h0_t0_out_)) + h0_rh;

    return humidity;
}

float HTS221_get_temperature(void) {

    if (I2C_read_data == NULL) {
        return -1;
    }

    uint8_t temperature_data[2];
    HTS221_read_array(HTS221_ADDRESS_TEMP_OUT_L, temperature_data, 2);
    int16_t temperature_raw = (temperature_data[1] << 8) | temperature_data[0];

    uint8_t t0_out[2], t1_out[2], t_degC_x8[2];
    uint8_t t0_t1_msb = HTS221_read_byte(HTS221_ADDRESS_T1_T2_msb);

    HTS221_read_array(HTS221_ADDRESS_T0_OUT_L, t0_out, 2);
    HTS221_read_array(HTS221_ADDRESS_T1_OUT_L, t1_out, 2);
    HTS221_read_array(HTS221_ADDRESS_T0_degC_x8, t_degC_x8, 2);

    int16_t t0_out_value = (int16_t)((t0_out[1] << 8) | t0_out[0]);
    int16_t t1_out_value = (int16_t)((t1_out[1] << 8) | t1_out[0]);

    uint16_t t0_degC = t_degC_x8[0];
    uint16_t t1_degC = t_degC_x8[1];

    t0_degC |= ((t0_t1_msb & 0x03) << 8);
    t1_degC |= ((t0_t1_msb & 0x0C) << 6);

    float t0_calibrated = t0_degC / 8.0f;
    float t1_calibrated = t1_degC / 8.0f;

    float temperature = ((t1_calibrated - t0_calibrated) / (t1_out_value - t0_out_value)) *
                        (temperature_raw - t0_out_value) + t0_calibrated;

    return temperature;
}







