/*
 * ESP8266.h
 *
 *  Created on: Mar 19, 2024
 *      Author: Menna Eid
 */

#ifndef INC_ESP8266_H_
#define INC_ESP8266_H_

#include "stdint.h"
#include "stm32f1xx.h"

/**
  * @brief  Initialize the ESP8266 WiFi module.
  * @note   This function sets the WiFi mode to station mode.
  * @retval None
  */
void ESP8266_wifi_init(uint8_t*response);

/**
  * @brief  Connect the ESP8266 module to a WiFi network.
  * @param  ssid: Pointer to the SSID (network name) of the WiFi network.
  * @param  password: Pointer to the password of the WiFi network.
  * @note   This function sends the AT command AT+CWJAP to the ESP8266 module to connect to the specified WiFi network.
  * @retval HAL_StatusTypeDef: HAL_OK if the connection was successful, HAL_ERROR otherwise.
  */
HAL_StatusTypeDef ESP8266_wifi_connect();

/**
  * @brief  Establish TCP socket connection with the specified server.
  * @param  server_ip: Pointer to the IP address of the server.
  * @param  server_port: Port number of the server.
  * @note   This function sends the AT command AT+CIPSTART to the ESP8266 module to establish a TCP socket connection with the specified server.
  * @retval HAL_StatusTypeDef: HAL_OK if the connection was successful, HAL_ERROR otherwise.
  */
HAL_StatusTypeDef ESP8266_socket_connect(const char* server_ip, uint32_t server_port);

/**
  * @brief  Send data packet over TCP connection.
  * @param  data: Pointer to the data packet to be sent.
  * @param  length: Length of the data packet.
  * @note   This function sends the specified data packet over the TCP connection.
  * @retval HAL_StatusTypeDef: HAL_OK if the data was sent successfully, HAL_ERROR otherwise.
  */
HAL_StatusTypeDef ESP8266_send_tcp_packet(const uint8_t* data, size_t length);
#endif /* INC_ESP8266_H_ */
