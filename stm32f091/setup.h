#pragma once

#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_i2c.h>
#include <stm32f0xx_hal_uart.h>

#include "consts.h"

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;

void ws_io_setup();

void NMI_Handler();
void HardFault_Handler();
void SysTick_Handler();
void HAL_MspInit();
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c);
void HAL_UART_MspInit(UART_HandleTypeDef *huart);
