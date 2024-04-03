/*
 * MQTT.h
 *
 *  Created on: Mar 19, 2024
 *      Author: Menna Eid
 */

#ifndef INC_MQTT_H_
#define INC_MQTT_H_

#include "stdint.h"
#include "stm32f1xx.h"
#include "ESP8266.h"
#include "string.h"
void MQTT_Connect(uint8_t*ID);

void MQTT_Publish(uint8_t*topic,uint8_t*msg,uint32_t len,uint8_t QOS);

//void MQTT_Subscribe(uint8_t*topic);


#endif /* INC_MQTT_H_ */
