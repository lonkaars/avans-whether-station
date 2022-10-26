#include <stm32f0xx_hal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stm32f0xx.h>

#include "esp8266.h"
#include "setup.h"
#include "consts.h"

char g_ws_esp8266_dma_rx_buffer[WS_DMA_RX_BUFFER_SIZE];
char MainBuf[WS_DMA_RX_BUFFER_SIZE]; // TODO: remove
int isOK = 0; // TODO: remove
uint16_t g_ws_esp8266_dma_old_pos = 0;
uint16_t g_ws_esp8266_dma_new_pos = 0;

/*
// when rx receives data handle the message. this function is in stm32. this name needs to stay the same or else it wont work.
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
	if(huart->Instance == USART1) {
		g_ws_esp8266_dma_old_pos = g_ws_esp8266_dma_new_pos;   // Update the last position before copying new data

		if(g_ws_esp8266_dma_old_pos+Size > WS_DMA_RX_BUFFER_SIZE) { // if the current position + new data is greater than the main buffer
			uint16_t dataToCopy = WS_DMA_RX_BUFFER_SIZE-g_ws_esp8266_dma_old_pos; // find remaining space left
			memcpy ((uint8_t*)MainBuf+g_ws_esp8266_dma_old_pos,g_ws_esp8266_dma_rx_buffer,dataToCopy); // copy data in the remaining space

			g_ws_esp8266_dma_old_pos = 0; // point to the start of the buffer
			memcpy ((uint8_t*)MainBuf,(uint8_t*)g_ws_esp8266_dma_rx_buffer+dataToCopy,(Size-dataToCopy)); // copy the remaing data
			g_ws_esp8266_dma_new_pos = (Size-dataToCopy); // update position
		}
		// if data is less than new data
		else {
			memcpy ((uint8_t*)MainBuf+g_ws_esp8266_dma_old_pos,g_ws_esp8266_dma_rx_buffer,Size);
			g_ws_esp8266_dma_new_pos = Size+g_ws_esp8266_dma_old_pos;
		}
		// start DMA again
		// memset(g_ws_esp8266_dma_rx_buffer,'\0',g_ws_esp8266_dma_rx_buffer_Size); // clear rx_buff
		HAL_UART_Receive_DMA(&huart1, (uint8_t*) g_ws_esp8266_dma_rx_buffer, WS_DMA_RX_BUFFER_SIZE);
		__HAL_DMA_DISABLE_IT(&hdma_usart1_rx,DMA_IT_HT);
	}

	// check for OK messagge
	for(int i=0;i<Size;i++){
		if(g_ws_esp8266_dma_rx_buffer[i]=='O' && g_ws_esp8266_dma_rx_buffer[i+1]=='K'){
			isOK=1;
		    //memset(MainBuf,'\0',MainBuf_Size); // clear main buffer if OK is in the main buffer.
		    //memset(g_ws_esp8266_dma_rx_buffer,'\0',g_ws_esp8266_dma_rx_buffer_Size); // clear rx_buff

		}
		else if(strncmp(g_ws_esp8266_dma_rx_buffer, "+IPD", 4) == 0){

		}
	}
}
*/

void DMA1_Ch1_IRQHandler(void) { HAL_DMA_IRQHandler(&hdma_usart1_rx); }
void DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler(void) { HAL_DMA_IRQHandler(&hdma_usart1_tx); }
void USART1_IRQHandler(void) { HAL_UART_IRQHandler(&huart1); }

void ws_esp8266_ATsendCommand(uint8_t* data){
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
int ws_esp8266_checkOK(uint8_t *receiveData,int length){
	 char *ret="";
	 // char *ret1="";
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
int ws_esp8266_receivingMsg(uint8_t *receiveData,int length){
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
int ws_esp8266_unlink(uint8_t *receiveData,int length){
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

void ws_esp8266_StartEsp(){
	uint8_t Tx_AT[]="AT\r\n";
	uint8_t Rx_buffer[10]={0};
	for(int i=0;i<3;i++){
   // HAL_UART_Transmit(&huart2, hier,sizeof(hier),100);
    HAL_UART_Transmit(&huart1, Tx_AT,strlen((char*)Tx_AT), 100);
	HAL_UART_Receive(&huart1, Rx_buffer, 10, 100);


 	HAL_UART_Transmit(&huart2, Rx_buffer,10,100);
 	HAL_Delay(5000);
 	//memset(Rx_buffer,0,sizeof(Rx_buffer));
	}

}
void ws_esp8266_disconnect(){
	int ret;
	uint8_t Tx_disconnect[]="AT+CWQAP\r\n";uint8_t buffer[17]={0};
	while(ret!=1){

	    HAL_UART_Transmit(&huart1, Tx_disconnect,strlen((char*)Tx_disconnect), 100);
		HAL_UART_Receive(&huart1, buffer, 17, 100);
		HAL_Delay(2000);

		if(ws_esp8266_checkOK(buffer,17)==1){
			ret=1;
		}

		}

	HAL_Delay(5000);
}
void ws_esp8266_mode(){
	int ret;
	uint8_t buffer1[20]={0};	uint8_t Tx_mode[]="AT+CWMODE=1\r\n";

	while(ret!=1){

	    HAL_UART_Transmit(&huart1, Tx_mode,strlen((char*)Tx_mode), 100);
		HAL_UART_Receive(&huart1, buffer1, 20, 100);
		HAL_Delay(1000);

		if(ws_esp8266_checkOK(buffer1,20)==1){
			ret=1;

		}

		}

	HAL_Delay(1000);
}
void ws_esp8266_connect(){
		uint8_t Tx_network[]="AT+CWJAP=\"" WS_ESP8266_WLAN_SSID "\",\"" WS_ESP8266_WLAN_PASSWD "\"\r\n";


		HAL_UART_Transmit(&huart1, Tx_network,strlen((char*)Tx_network),1000);
		HAL_Delay(10000);
//		HAL_UART_Transmit(&huart1, Tx_network,sizeof(Tx_network),1000);
//		HAL_Delay(10000);





}
void ws_esp8266_serveraan(){
	int ret;
	uint8_t buffer1[30]={0};	uint8_t Tx_server[]="AT+CIPSERVER=1," WS_SERVER_PORT "\r\n";

	while(ret!=1){

	    HAL_UART_Transmit(&huart1, Tx_server,strlen((char*)Tx_server), 100);
		HAL_UART_Receive(&huart1, buffer1, 30, 100);
		HAL_Delay(2000);

		if(ws_esp8266_checkOK(buffer1,30)==1){
			ret=1;

		}

		}

	HAL_Delay(1000);
}
void ws_esp8266_serveruit(){
	//int ret;
	//uint8_t buffer1[27]={0};
	uint8_t Tx_server[]="AT+CIPSERVER=0\r\n";
//
//	while(ret!=1){

	    HAL_UART_Transmit(&huart1, Tx_server,strlen((char*)Tx_server), 100);
//		HAL_UART_Receive(&huart1, buffer1, 27, 100);
		HAL_Delay(3000);

//		if(unlink(buffer1,27)==1){
//			ret=1;
//
//		}
//
//		}

	HAL_Delay(1000);
}
void ws_esp8266_mux(){
	int ret;
	uint8_t buffer2[20]={0};	uint8_t Tx_mux[]="AT+CIPMUX=1\r\n";

	while(ret!=1){

	    HAL_UART_Transmit(&huart1, Tx_mux,strlen((char*)Tx_mux), 100);
		HAL_UART_Receive(&huart1, buffer2, 20, 100);
		HAL_Delay(2000);

		if(ws_esp8266_checkOK(buffer2,20)==1){
			ret=1;

		}

		}

	HAL_Delay(5000);
}
void ws_esp8266_close(){

	uint8_t Tx_close[]="AT+CIPCLOSE=0\r\n";


	    HAL_UART_Transmit(&huart1, Tx_close,strlen((char*)Tx_close), 100);

		HAL_Delay(3000);

}

