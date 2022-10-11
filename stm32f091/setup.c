#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_rcc.h>
#include <stm32f0xx_hal_i2c.h>
#include <stm32f0xx_hal_uart.h>
#include <FreeRTOS.h>
#include <task.h>

#include "setup.h"

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart2;

static void ws_io_clock_setup();
static void ws_io_i2c_setup();
static void ws_io_usart2_setup();
static void ws_setup_error_handler();

void ws_io_setup() {
	HAL_Init();

	ws_io_clock_setup();
	ws_io_i2c_setup();
	ws_io_usart2_setup();
}

static void ws_io_clock_setup() {
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	/** Initializes the RCC Oscillators according to the specified parameters in
	 * the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
	RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) return ws_setup_error_handler();

	/** Initializes the CPU, AHB and APB buses clocks */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
		|RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) return ws_setup_error_handler();
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_I2C1;
	PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
	PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) return ws_setup_error_handler();
}

static void ws_io_i2c_setup() {
	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = 0x2000090E;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK) return ws_setup_error_handler();
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK) return ws_setup_error_handler();
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK) return ws_setup_error_handler();
}

static void ws_io_usart2_setup() {
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart2) != HAL_OK) return ws_setup_error_handler();
}

void HAL_MspInit() {
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
  HAL_NVIC_SetPriority(PendSV_IRQn, 3, 0);
}

void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c) {
  if(hi2c->Instance != I2C1) return;

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9; //TODO: use #defines in setup.h
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF1_I2C1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	__HAL_RCC_I2C1_CLK_ENABLE();
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {
  if(huart->Instance != USART2) return;

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin = WS_PINOUT_USART_TX_PIN | WS_PINOUT_USART_RX_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF1_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void SysTick_Handler() {
	HAL_IncTick();
	if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) xPortSysTickHandler();
}

static void ws_setup_error_handler() {
	__disable_irq();
	for(;;);
}

void NMI_Handler() {
	for(;;);
}

void HardFault_Handler() {
	for(;;);
}
