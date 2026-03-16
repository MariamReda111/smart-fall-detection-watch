/*
 * GccApplication2.c
 *
 * Created: 15/03/2026 20:50:39
 * Author : maria
 */ 

//#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#inlcude "../MCAL/UART/uart.h"
#include "../HAL/LCD/lcd.h"
#include "../HAL/WIFI/wifi.h"

int main(void)
{
	UART_Init();
	LCD_init();

	LCD_displayString("System Boot");

	WIFI_Init();

	LCD_clearScreen();
	LCD_displayString("Connecting WiFi");

	if (WIFI_Connect())
	{
		LCD_clearScreen();
		LCD_displayString("WiFi Connected");
	}
	else
	{
		LCD_clearScreen();
		LCD_displayString("WiFi Failed");
		while(1);
	}

	uint8_t counter = 0;

	while(1)
	{
		/* Example Blynk update */
		WIFI_SendBlynkValue(counter);

		LCD_clearScreen();
		LCD_displayString("Blynk Sent");

		counter++;
		if(counter > 100)
		counter = 0;

		/* Example Telegram alert (for testing) */
		if(counter == 10)
		{
			WIFI_SendTelegramAlert("Emergency_Fall_Detected");
		}

		_delay_ms(1500);
	}
}

