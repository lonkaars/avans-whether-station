#include <FreeRTOS.h>
#include <task.h>
#include <stm32f0xx_hal.h>

#include "setup.h"
#include "sensor.h"
#include "backlog.h"

#define SI7021_ADDRESS ((uint16_t)(0x40) << 1)
#define BMP280_ADDRESS ((uint16_t)(0x76) << 1)
#define REG_TEMP ((uint8_t)(0xE3))
#define REG_HUM ((uint8_t)(0xF5))

uint8_t ws_sensor_temperature() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
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
	uint8_t buf[12];
	uint8_t buffer[12];
	int16_t val;

	buf[0]= 0xF4;
	buf[1]= 0x07;
	buffer[0] = 0xF7;
	HAL_I2C_Master_Transmit(&hi2c1, BMP280_ADDRESS, buf , 2, HAL_MAX_DELAY);
	HAL_I2C_Mem_Read(&hi2c1, BMP280_ADDRESS, 0xF7, 1, buffer, 2, 100 );
	val = (buffer[0] << 8 | buffer[1]);

	return (uint8_t) val; // TODO: convert with range
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
		vTaskDelay(portTICK_PERIOD_MS * 1000 * 1);
	}
}

