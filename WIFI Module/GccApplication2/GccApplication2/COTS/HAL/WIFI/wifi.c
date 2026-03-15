/*
 * wifi.c
 *
 * Created: 15/03/2026 21:30:42
 *  Author: maria
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include "../../MCAL/UART/uart.h"
#include "wifi.h"

void WIFI_Init(void)
{
	_delay_ms(3000);  // wait for ESP8266 boot

	UART_SendString("AT\r\n");
	UART_WaitFor("OK");

	/* Set station mode */
	UART_SendString("AT+CWMODE=1\r\n");
	UART_WaitFor("OK");
}

/* -------------------------------------------------- */
/* Connect to WiFi */
/* -------------------------------------------------- */

uint8_t WIFI_Connect(void)
{
	char cmd[100];

	sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", WIFI_SSID, WIFI_PASSWORD);
	UART_SendString(cmd);

	if (UART_WaitFor("WIFI GOT IP"))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/* -------------------------------------------------- */
/* Send Data to Blynk */
/* -------------------------------------------------- */

void WIFI_SendBlynkValue(uint8_t value)
{
	char httpRequest[200];
	char cmd[40];

	sprintf(httpRequest,
	"GET /external/api/update?token=%s&v1=%d HTTP/1.1\r\n"
	"Host: blynk.cloud\r\n"
	"Connection: close\r\n\r\n",
	BLYNK_AUTH_TOKEN, value);

	UART_SendString("AT+CIPSTART=\"TCP\",\"blynk.cloud\",80\r\n");
	UART_WaitFor("OK");

	sprintf(cmd, "AT+CIPSEND=%d\r\n", strlen(httpRequest));
	UART_SendString(cmd);

	UART_WaitFor(">");

	UART_SendString(httpRequest);

	UART_WaitFor("SEND OK");
}

/* -------------------------------------------------- */
/* Send Telegram Alert */
/* -------------------------------------------------- */

void WIFI_SendTelegramAlert(char *message)
{
	char httpRequest[300];
	char cmd[40];

	sprintf(httpRequest,
	"GET /bot%s/sendMessage?chat_id=%s&text=%s HTTP/1.1\r\n"
	"Host: api.telegram.org\r\n"
	"Connection: close\r\n\r\n",
	TELEGRAM_BOT_TOKEN, TELEGRAM_CHAT_ID, message);

	UART_SendString("AT+CIPSTART=\"TCP\",\"api.telegram.org\",80\r\n");
	UART_WaitFor("OK");

	sprintf(cmd, "AT+CIPSEND=%d\r\n", strlen(httpRequest));
	UART_SendString(cmd);

	UART_WaitFor(">");

	UART_SendString(httpRequest);

	UART_WaitFor("SEND OK");
}