/*
 * MQTT.c
 *
 *  Created on: Mar 19, 2024
 *      Author: Menna Eid
 */

#include "MQTT.h"

extern UART_HandleTypeDef  huart2;
uint8_t packet[200] = {0};
uint8_t packetindex = 0;
uint16_t packetId  = 1;

const char* protocolName ="MQTT";
void MQTT_Connect(uint8_t*ID)
{
	// establish TCP connection
	ESP8266_socket_connect("test.mosquitto.org",1883);

	uint8_t remlen = (12+strlen(ID));
	packetindex = 0;
	// encode packet
	packet[packetindex++] = 0x10; // packet type --> client
	packet[packetindex++] = remlen;
	packet[packetindex++] = 0x00;
	packet[packetindex++] = 0x04; // size of protocol name
	strcpy(packet+packetindex,protocolName);
	packetindex +=4;

	packet[packetindex++] = 0x04; // level or version
	packet[packetindex++] = 0x02; // flags = clean session only , public broker is used
	packet[packetindex++] = 0xFF; // keep alive time  = 18h
	packet[packetindex++] = 0xFF;

	packet[packetindex++] = 0x00;
	packet[packetindex++] = strlen(ID); // size of protocol name
	strcpy(packet+packetindex,ID);
	packetindex += strlen(ID);

	// send packet
	while(ESP8266_send_tcp_packet(packet, packetindex)!=0)
	{
		ESP8266_send_tcp_packet(packet, packetindex);
	}
	ESP8266_socket_connect("test.mosquitto.org",1883);

}

void MQTT_Publish(uint8_t*topic,uint8_t*msg,uint32_t len,uint8_t QOS)
{
	uint8_t msgIndex = 0;
	uint8_t remlen = (2+strlen(topic)+len);
	packetindex = 0;
	// encode packet
	if(QOS==1)
	{
		remlen +=2;
		packet[packetindex++] = 0x32; // packet type
	}
	else {
		packet[packetindex++] = 0x30; // packet type
	}

	packet[packetindex++] = remlen;
	packet[packetindex++] = 0x00;
	packet[packetindex++] = strlen(topic);
	strcpy(packet+packetindex,topic);
	packetindex +=strlen(topic);
	// send packetid
	if(QOS>0)
	{
		packet[packetindex++] = (uint8_t)(packetId>>8);
		packet[packetindex++] = (uint8_t)packetId;
		packetId++;
	}
	for(msgIndex=0;msgIndex<len;msgIndex++)
	{
		packet[packetindex++] = msg[msgIndex];

	}

	// send packet
	while(ESP8266_send_tcp_packet(packet, packetindex)!=0)
	{
		ESP8266_send_tcp_packet(packet, packetindex);
	}


}

/*void MQTT_Subscribe(uint8_t*topic)
{

}*/
