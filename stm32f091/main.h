#pragma once

#include <stm32f0xx_hal_i2c.h>
#include <stm32f0xx_hal_uart.h>

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;

void task_1();
int main();
