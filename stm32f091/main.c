#include <FreeRTOS.h>
#include <task.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_msp.h>

#include "main.h"
#include "setup.h"
#include "sensor.h"
#include "backlog.h"

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart2;

int main() {
	HAL_Init();

	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	MX_I2C2_Init();

	HAL_I2C_MspInit(&hi2c1);

	ws_backlog_alloc(24 * 60);
	ws_sensor_read();

	xTaskCreate(ws_sensor_read_task, "sensor", 128, NULL, 1, NULL);
	vTaskStartScheduler();
}
