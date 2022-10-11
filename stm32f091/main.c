#include <FreeRTOS.h>
#include <task.h>
#include <stm32f0xx_hal.h>

#include "main.h"
#include "setup.h"
#include "sensor.h"
#include "backlog.h"

int main() {
	ws_io_setup();
	HAL_GPIO_Init(GPIOA, &(GPIO_InitTypeDef) {
		.Pin = GPIO_PIN_5,
		.Mode = GPIO_MODE_OUTPUT_PP,
		.Pull = GPIO_NOPULL
	});

	ws_backlog_alloc(24 * 60);
	ws_sensor_read();

	xTaskCreate(ws_sensor_read_task, "sensor", 128, NULL, 1, NULL);
	vTaskStartScheduler();
}
