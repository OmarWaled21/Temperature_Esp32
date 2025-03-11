#include "Utilities.h"
#include <Globals.h>

int documentCounter = 0;

String generateDeviceId() {

  // Get or create device ID components
  uint32_t chipId = (uint32_t)(ESP.getEfuseMac() & 0xFFFFFFFF);
  String deviceId = getDeviceIdFromSD();

  if (deviceId.isEmpty()) {
    int counter = getCounterFromSD() + 1;
    deviceId = "ESP32-esp{" + String(chipId) + "-" + String(counter) + "}";
    saveDeviceIdToSD(deviceId);
    saveCounterToSD(counter);
    Serial.printf("Generated new device ID: %s\n", deviceId.c_str());
  }

  return deviceId;
}