/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void ATsendCommand(uint8_t* data){
	char dataChar[20];
	uint8_t Tx_send[]="AT+CIPSEND=0,";

	itoa(strlen((char*)data),dataChar,10);
	strcat((char*)Tx_send,dataChar);
	strcat((char*)Tx_send,"\r\n");
	HAL_UART_Transmit(&huart1, Tx_send, strlen((char*)Tx_send),1000);
	HAL_Delay(2000);
	HAL_UART_Transmit(&huart1, data, strlen((char*)data),1000);
	HAL_Delay(1000);
	HAL_UART_Transmit(&huart2, data, strlen((char*)data),1000);
	HAL_Delay(5000);
}
int checkOK(uint8_t *receiveData,int length){
	 char *ret="";
	 char *ret1="";
	 HAL_UART_Transmit(&huart2, receiveData,length,1000);
 	 ret = strstr((char*)receiveData,"OK");
 	// ret = strstr((char*)receiveData,"change");
 	// memset(receiveData,0,30);
 	 if((ret[0]='O') && (ret[1]=='K')){
 		//HAL_UART_Transmit(&huart2, (uint8_t*)ret, sizeof(ret), 100);
 		return 1;

 	 }
// 	 else if((ret1[0]='c') && (ret1[1]=='h')){
// 		//HAL_UART_Transmit(&huart2, (uint8_t*)ret, sizeof(ret), 100);
// 		return 1;
//
// 	 }
 	 else{
 		 return 0;
 	 }

}
int receivingMsg(uint8_t *receiveData,int length){
	 char *ret="";
	 HAL_UART_Transmit(&huart2, receiveData,length,1000);
 	 ret = strstr((char*)receiveData,"+IPD");
 	// memset(receiveData,0,30);
 	 if((ret[0]='+') && (ret[1]=='I')){
 		//HAL_UART_Transmit(&huart2, (uint8_t*)ret, sizeof(ret), 100);
 		return 1;

 	 }
 	 else{
 		 return 0;
 	 }

}
int unlink(uint8_t *receiveData,int length){
	 char *ret="";
	 HAL_UART_Transmit(&huart2, receiveData,length,1000);
 	 ret = strstr((char*)receiveData,"UNLINK");
 	// memset(receiveData,0,30);
 	 if((ret[0]='U') && (ret[1]=='N')){
 		//HAL_UART_Transmit(&huart2, (uint8_t*)ret, sizeof(ret), 100);
 		return 1;

 	 }
 	 else{
 		 return 0;
 	 }

}

void StartEsp(){

	uint8_t Tx_AT[]="AT\r\n";
	uint8_t Rx_buffer[10]={0};
	for(int i=0;i<3;i++){
   // HAL_UART_Transmit(&huart2, hier,sizeof(hier),100);
    HAL_UART_Transmit_IT(&huart1, Tx_AT,strlen((char*)Tx_AT));
	HAL_UART_Receive_IT(&huart1, Rx_buffer, 10);


 	HAL_UART_Transmit(&huart2, Rx_buffer,10,100);
 	HAL_Delay(5000);
 	//memset(Rx_buffer,0,sizeof(Rx_buffer));
	}

}
void disconnect(){
	int ret;
	uint8_t Tx_disconnect[]="AT+CWQAP\r\n";uint8_t buffer[17]={0};
	while(ret!=1){

	    HAL_UART_Transmit_IT(&huart1, Tx_disconnect,strlen((char*)Tx_disconnect));
		HAL_UART_Receive_IT(&huart1, buffer, 17);
		HAL_Delay(2000);

		if(checkOK(buffer,17)==1){
			ret=1;
		}

		}

	HAL_Delay(5000);
}
void mode(){
	int ret;
	uint8_t buffer1[20]={0};	uint8_t Tx_mode[]="AT+CWMODE=1\r\n";

	while(ret!=1){

	    HAL_UART_Transmit_IT(&huart1, Tx_mode,strlen((char*)Tx_mode));
		HAL_UART_Receive_IT(&huart1, buffer1, 20);
		HAL_Delay(1000);

		if(checkOK(buffer1,20)==1){
			ret=1;

		}

		}

	HAL_Delay(1000);
}
void connect(){
		uint8_t Tx_network[]="AT+CWJAP=\"Test\",\"12345678\"\r\n";


		HAL_UART_Transmit(&huart1, Tx_network,strlen((char*)Tx_network),1000);
		HAL_Delay(10000);
//		HAL_UART_Transmit(&huart1, Tx_network,sizeof(Tx_network),1000);
//		HAL_Delay(10000);





}
void serveraan(){
	int ret;
	uint8_t buffer1[30]={0};	uint8_t Tx_server[]="AT+CIPSERVER=1,80\r\n";

	while(ret!=1){

	    HAL_UART_Transmit_IT(&huart1, Tx_server,strlen((char*)Tx_server));
		HAL_UART_Receive_IT(&huart1, buffer1, 30);
		HAL_Delay(2000);

		if(checkOK(buffer1,30)==1){
			ret=1;

		}

		}

	HAL_Delay(1000);
}
void serveruit(){
	int ret;
	uint8_t buffer1[27]={0};	uint8_t Tx_server[]="AT+CIPSERVER=0\r\n";
//
//	while(ret!=1){

	    HAL_UART_Transmit_IT(&huart1, Tx_server,strlen((char*)Tx_server));
//		HAL_UART_Receive_IT(&huart1, buffer1, 27);
		HAL_Delay(3000);

//		if(unlink(buffer1,27)==1){
//			ret=1;
//
//		}
//
//		}

	HAL_Delay(1000);
}
void mux(){
	int ret;
	uint8_t buffer2[20]={0};	uint8_t Tx_mux[]="AT+CIPMUX=1\r\n";

	while(ret!=1){

	    HAL_UART_Transmit_IT(&huart1, Tx_mux,strlen((char*)Tx_mux));
		HAL_UART_Receive_IT(&huart1, buffer2, 20);
		HAL_Delay(2000);

		if(checkOK(buffer2,20)==1){
			ret=1;

		}

		}

	HAL_Delay(5000);
}
void close(){

	uint8_t Tx_close[]="AT+CIPCLOSE=0\r\n";


	    HAL_UART_Transmit_IT(&huart1, Tx_close,strlen((char*)Tx_close));

		HAL_Delay(3000);

}

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
uint8_t ok[]= "ok\r\n";
uint8_t hier[]= "hier\r\n";
//disconnect();//connect();//

StartEsp();
HAL_UART_Transmit(&huart2, hier,sizeof(hier),1000);
close();
HAL_UART_Transmit(&huart2, hier,sizeof(hier),1000);
serveruit();
HAL_UART_Transmit(&huart2, hier,sizeof(hier),1000);
mux();
HAL_UART_Transmit(&huart2, hier,sizeof(hier),1000);
mode();
HAL_UART_Transmit(&huart2, hier,sizeof(hier),1000);

serveraan();
HAL_UART_Transmit(&huart2, ok,sizeof(ok),1000);
uint8_t receive[24]={0};
uint8_t sendToQTData[]="gelukt";
uint8_t test[]="test";
int ret;
//ATsendCommand(sendToQTData);
  while (1)
  {

		if(receive[0]=='\0')
		{
			HAL_UART_Receive_IT(&huart1, receive, 24);
		}
		else
		{
			HAL_UART_Transmit(&huart2, test,strlen((char*)test),1000);
			HAL_Delay(5000);

//			if(receivingMsg(receive, 24)==1)
//			{
//			ret=1;
			ATsendCommand(sendToQTData);
			close();
			memset(receive,0,24);
			//}
		}



	}





}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
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
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
