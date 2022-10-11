#include <FreeRTOS.h>
#include <task.h>
#include <stm32f0xx_hal.h>

#include "main.h"
#include "sensor.h"
#include "backlog.h"

#define SI7021_ADDRESS ((uint16_t)(0x40) << 1)
#define REG_TEMP ((uint8_t)(0xE3))
#define REG_HUM ((uint8_t)(0xF5))

uint8_t ws_sensor_temperature() {
	uint8_t buf[12];
	int16_t val;
	float temp_c;
	buf[0] = REG_TEMP;
	HAL_I2C_Master_Transmit(&hi2c1, SI7021_ADDRESS, buf, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&hi2c1, SI7021_ADDRESS, buf, 2, HAL_MAX_DELAY);
	val = ((int16_t)buf[0]<< 8 ) | (buf[1]);
	temp_c= ((175.72*val)/65536) - 46.85;

	return (uint8_t) temp_c; //TODO: convert with range -> util.h
}

uint8_t ws_sensor_humidity() {
	return 0x00;
}

uint8_t ws_sensor_atmospheric_pressure() {
	return 0x00;
}

void ws_sensor_read() {
	ws_s_backlog_record record = {
		.sens_temperature = ws_sensor_temperature(),
		.sens_atm_pressure = ws_sensor_atmospheric_pressure(),
		.sens_humidity = ws_sensor_humidity()
	};
	ws_backlog_add_record(record);
}

void ws_sensor_read_task() {
	while (1) {
		ws_sensor_read();
		vTaskDelay(portTICK_PERIOD_MS * 1000 * 60);
	}
}

