#include <stm32f0xx_hal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "setup.h"
#include "server.h"
#include "esp8266.h"

void ws_server_demo() {
	uint8_t ok[]= "ok\r\n";
	uint8_t hier[]= "hier\r\n";
	//disconnect();//connect();//

	ws_esp8266_StartEsp();
	HAL_UART_Transmit(&huart2, hier,sizeof(hier),1000);
	ws_esp8266_close();
	HAL_UART_Transmit(&huart2, hier,sizeof(hier),1000);
	ws_esp8266_serveruit();
	HAL_UART_Transmit(&huart2, hier,sizeof(hier),1000);
	ws_esp8266_mux();
	HAL_UART_Transmit(&huart2, hier,sizeof(hier),1000);
	ws_esp8266_mode();
	HAL_UART_Transmit(&huart2, hier,sizeof(hier),1000);

	ws_esp8266_serveraan();
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
				ws_esp8266_ATsendCommand(sendToQTData);
				ws_esp8266_close();
				memset(receive,0,24);
				//}
			}



		}
}
