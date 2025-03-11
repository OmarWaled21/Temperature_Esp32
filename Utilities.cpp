#include "Utilities.h"
#include <Globals.h>

int documentCounter = 0;

String generateDeviceId() {

  // Get or create device ID components
  uint32_t chipId = (uint32_t)(ESP.getEfuseMac() & 0xFFFFFFFF);
  String deviceId = getStringPreference("user", "device_id");

  if (deviceId.isEmpty()) {
    int counter = getIntPreference("user", "devCounter") + 1;
    deviceId = "ESP32-esp{" + String(chipId) + "-" + String(counter) + "}";
    saveStringPreference("user", "device_id", deviceId);
    saveIntPreference("user", "devCounter", counter);
    Serial.printf("Generated new device ID: %s\n", deviceId.c_str());
  }

  return deviceId;
}


// Function to save a string value in Preferences
void saveStringPreference(const String &namespaceName, const String &key, const String &value) {
  preferences.begin(namespaceName.c_str(), false);  // Open in write mode
  preferences.putString(key.c_str(), value);
  preferences.end();
  Serial.println("✅ Saved: " + key + " = " + value);
}

void saveIntPreference(const String &namespaceName, const String &key, const int &value) {
  preferences.begin(namespaceName.c_str(), false);  // Open in write mode
  preferences.putInt(key.c_str(), value);
  preferences.end();
  Serial.println("✅ Saved: " + key + " = " + value);
}

// Function to retrieve a string value from Preferences
String getStringPreference(const String &namespaceName, const String &key, const String &defaultValue) {
  preferences.begin(namespaceName.c_str(), true);  // Open in read mode
  String value = preferences.getString(key.c_str(), defaultValue);
  preferences.end();
  Serial.println("📥 Retrieved: " + key + " = " + value);
  return value;
}
int getIntPreference(const String &namespaceName, const String &key, const int &defaultValue) {
  preferences.begin(namespaceName.c_str(), true);  // Open in read mode
  int value = preferences.getInt(key.c_str(), defaultValue);
  preferences.end();
  Serial.println("📥 Retrieved: " + key + " = " + value);
  return value;
}
void removePreference(const String &namespaceName, const String &key) {
  preferences.begin(namespaceName.c_str(), false);  // Open in read mode
  preferences.remove(key.c_str());
  preferences.end();
  Serial.println("📥 Removed: " + key);
}
