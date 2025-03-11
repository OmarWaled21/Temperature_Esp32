#ifndef GLOBALS_H
#define GLOBALS_H

#include <WiFi.h>
#include <WebServer.h>
#include <WiFiUdp.h>
#include <Preferences.h>
#include <BluetoothSerial.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <time.h>

extern Preferences preferences; // Only declared here
extern WiFiUDP udp;
extern BluetoothSerial SerialBT; // Define it only here
extern bool isBlueToothActivate;

#endif
