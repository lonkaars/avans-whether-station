#include <FreeRTOS.h>
#include <task.h>
#include <stm32f0xx_hal.h>

#include "main.h"
#include "setup.h"
#include "sensor.h"

#include "test.h"

int main() {
	ws_io_setup();
	// xTaskCreate(ws_sensor_read_task, "sensor", 64, NULL, 1, NULL);
	xTaskCreate(ws_test_write_task, "testw", 16, NULL, 2, NULL);
	xTaskCreate(ws_test_read_task, "testr", 16, NULL, 2, NULL);
	vTaskStartScheduler();
}
