/*
 * ESP8266.c
 *
 *  Created on: Mar 19, 2024
 *      Author: Menna Eid
 */


#include "ESP8266.h"
/*
 * u8 res [3]-->
 **/
extern UART_HandleTypeDef huart2;

void ESP8266_wifi_init(uint8_t*response)
{
	HAL_UART_Transmit(&huart2,"AT+RST\r\n", strlen("AT+RST\r\n"), 1000);
	HAL_Delay(2000);
	HAL_UART_Transmit(&huart2,"AT+UART_DEF=115200,8,1,0,0\r\n",strlen("AT+UART_DEF=115200,8,1,0,0\r\n"),1000);
	HAL_Delay(2000);
	HAL_UART_Transmit(&huart2,"AT\r\n", strlen("AT\r\n"), 1000);
	HAL_Delay(200);
	HAL_UART_Receive(&huart2,response, 3,1000);
	HAL_Delay(2000);
	HAL_UART_Transmit(&huart2,"AT+CWMODE=1\r\n", strlen("AT+CWMODE=1\r\n"), 1000);
	HAL_Delay(2000);
}
HAL_StatusTypeDef ESP8266_wifi_connect()
{
	// enable DHCP
	HAL_UART_Transmit(&huart2,"AT+CWDHCP=1,1\r\n",strlen("AT+CWDHCP=1,1\r\n"),1000);
	HAL_UART_Delay(200);
	// set SSID and Password
	if(HAL_UART_Transmit(&huart2,"AT+CWJAP_CUR=\"Menna\",\"123456789\"\r\n", strlen("AT+CWJAP_CUR=\"MM\",\"EmbeddedSystem\"\r\n"), 10000)!=HAL_OK)
	{
		return HAL_ERROR;
	}
   return HAL_OK;
}


HAL_StatusTypeDef ESP8266_socket_connect(const char* server_ip,uint32_t server_port)
{
    char cmd_buffer[50]; // Buffer for AT command

    /*  AT command for TCP socket connection */
    snprintf(cmd_buffer, sizeof(cmd_buffer), "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", server_ip, server_port);

    /* Send AT command to establish TCP socket connection */
    if (HAL_UART_Transmit(&huart2, (const uint8_t*)cmd_buffer, strlen(cmd_buffer), 1000) != HAL_OK) {
        return HAL_ERROR;
    }
    HAL_Delay(2000);

    return HAL_OK; // TCP socket connection established successfully
}

HAL_StatusTypeDef ESP8266_send_tcp_packet(const uint8_t* data, size_t length)
{
    char cmd_buffer[20]; // Buffer for constructing AT command

    /* Construct AT command for sending data */
    snprintf(cmd_buffer, sizeof(cmd_buffer), "AT+CIPSEND=%d\r\n", length);

    /* Send AT command to specify data length */
    if (HAL_UART_Transmit(&huart2,cmd_buffer, strlen(cmd_buffer), 1000) != HAL_OK) {
        return HAL_ERROR;
    }
    HAL_Delay(1000);

    /* Send data packet over TCP connection */
    if (HAL_UART_Transmit(&huart2, data, length, 1000) != HAL_OK) {
        return HAL_ERROR;
    }

    HAL_Delay(1000);


    return HAL_OK; // Data packet sent successfully
}

