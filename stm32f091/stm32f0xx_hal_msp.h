#pragma once

#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_uart.h>

void HAL_MspInit(void);
void HAL_UART_MspInit(UART_HandleTypeDef* huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart);

