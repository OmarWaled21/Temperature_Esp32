#ifndef GLOBALS_H
#define GLOBALS_H

#include <BluetoothSerial.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <SD.h>

extern WiFiUDP udp;
extern BluetoothSerial SerialBT;  // Define it only here
extern SPIClass spi;

// SD Card Pin Definitions
#define SD_SCK 25
#define SD_MISO 32
#define SD_MOSI 33
#define SD_CS 26

// 🔹 Initialize SD Card
bool initSDCard();

// 🔹 Wi-Fi Credentials Handling
bool saveWiFiCredentialsToSD(const String& ssid, const String& password);
bool loadWiFiCredentialsFromSD(String& ssid, String& password);
bool clearWiFiCredentialsFromSD();

// 🔹 User and Device ID Handling
bool saveUserIdToSD(const String& userId);
String getUserIdFromSD();
bool removeUserIdFromSD();

bool saveDeviceIdToSD(const String& deviceId);
String getDeviceIdFromSD();

// 🔹 Device Measurement Period Handling
bool saveDurationToSD(int duration);
int getDurationFromSD();

// 🔹 counter of generating device
bool saveCounterToSD(int counter);
int getCounterFromSD();

#endif
