#pragma once

#define HSE_VALUE 8000000U
#define HSE_STARTUP_TIMEOUT 100U
#define HSI_VALUE 8000000U
#define HSI_STARTUP_TIMEOUT 5000U
#define HSI14_VALUE 14000000U
#define HSI48_VALUE 48000000U
#define LSI_VALUE 40000U
#define LSE_VALUE 32768U
#define LSE_STARTUP_TIMEOUT 5000U
#define VDD_VALUE 3300U
#define TICK_INT_PRIORITY ((uint32_t)(1U<<__NVIC_PRIO_BITS) - 1U)
#define USE_RTOS 0U
#define PREFETCH_ENABLE 1U
#define INSTRUCTION_CACHE_ENABLE 0U
#define DATA_CACHE_ENABLE 0U
#define USE_SPI_CRC 1U

#define HAL_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_I2C_MODULE_ENABLED
#define HAL_I2S_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_RTC_MODULE_ENABLED
#define HAL_UART_MODULE_ENABLED
#define HAL_USART_MODULE_ENABLED

#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_dma.h>
#include <stm32f0xx_hal_gpio.h>
#include <stm32f0xx_hal_cortex.h>
#include <stm32f0xx_hal_flash.h>
#include <stm32f0xx_hal_i2c.h>
#include <stm32f0xx_hal_i2s.h>
#include <stm32f0xx_hal_pwr.h>
#include <stm32f0xx_hal_rtc.h>
#include <stm32f0xx_hal_uart.h>
#include <stm32f0xx_hal_usart.h>

