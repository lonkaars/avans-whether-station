#include <FreeRTOS.h>
#include <task.h>
#include <Si7021_driver.h>

#include "sensor.h"
#include "backlog.h"

uint8_t ws_sensor_temperature() {
	float temp = 0.f;
	r_single_Si7021(&temp, Temperature);
	return (uint8_t) temp; //TODO: convert with range -> util.h
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

