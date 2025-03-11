#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WiFi.h>
#include <BluetoothManager.h>
#include <Utilities.h>
#include <RTC.h>
#include <SD_Module.h>

void connectToWiFi();
void clearWifiCredentials();

#endif