/*
 * wifi.h
 *
 * Created: 15/03/2026 21:31:27
 *  Author: maria
 */ 


#ifndef WIFI_H_
#define WIFI_H_

/* Replace with your WiFi credentials */
#define WIFI_SSID       "nana"
#define WIFI_PASSWORD   "01023025564"

/* Replace with your Blynk token if you use Blynk */
#define BLYNK_AUTH_TOKEN   "tXaS2EX1wjwMv1SvCIz-si2XfgGck52e"

/* Replace with your Telegram bot token */
#define TELEGRAM_BOT_TOKEN "8224115321:AAE3T13qW805CE85Kw_zlYL66ruF9M26FsI"

/* Replace with your Telegram chat ID */
#define TELEGRAM_CHAT_ID   "6243078279"

/* ======================================================= */

/* WiFi control */
void WIFI_Init(void);
uint8_t WIFI_Connect(void);

/* Blynk communication */
void WIFI_SendBlynkValue(uint8_t value);

/* Telegram alert */
void WIFI_SendTelegramAlert(char *message);

void Telegram_Init(void);

void Telegram_SendMessage(char *message);

void Telegram_SendEmergency(int heartRate);

void Telegram_CheckCommands(void);



#endif /* WIFI_H_ */