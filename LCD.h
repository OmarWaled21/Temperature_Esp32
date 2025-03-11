#ifndef LCD_H
#define LCD_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

void initLcd();
void connectingWiFiLcd();
void connectedToWiFiLcd();
void lcdClear();
void showUserAndDeviceIdLcd(String userId, String deviceId);
void noUserIdLcd();
void showDataLcd(float temperature, int humidity);
void noSDCardLcd();
void sensorErrorLcd();

#endif