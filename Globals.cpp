#include "Globals.h"

// Define global variables
WiFiUDP udp;
BluetoothSerial SerialBT;

SPIClass spi = SPIClass(VSPI);

// 🔹 Initialize SD Card
bool initSDCard() {
    spi.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
    if (!SD.begin(SD_CS, spi)) {
        Serial.println("❌ SD Card initialization failed!");
        return false;
    }
    Serial.println("✅ SD Card is ready.");
    return true;
}

// 🔹 Save Wi-Fi Credentials to SD Card
bool saveWiFiCredentialsToSD(const String& ssid, const String& password) {
    File file = SD.open("/wifi.txt", FILE_WRITE);
    if (file) {
        file.println(ssid);
        file.println(password);
        file.close();
        Serial.println("✅ Wi-Fi credentials saved to SD Card.");
        return true;
    } else {
        Serial.println("❌ Failed to save Wi-Fi credentials to SD Card!");
        return false;
    }
}

// 🔹 Load Wi-Fi Credentials from SD Card
bool loadWiFiCredentialsFromSD(String &ssid, String &password) {
    File file = SD.open("/wifi.txt", FILE_READ);
    if (file) {
        ssid = file.readStringUntil('\n');
        password = file.readStringUntil('\n');
        ssid.trim();
        password.trim();
        file.close();
        Serial.println("✅ Wi-Fi credentials loaded from SD Card.");
        return true;
    } else {
        Serial.println("❌ No Wi-Fi credentials found on SD Card!");
        return false;
    }
}

// 🔹 Clear Wi-Fi Credentials from SD Card
bool clearWiFiCredentialsFromSD() {
    if (SD.exists("/wifi.txt")) {
        SD.remove("/wifi.txt");
        Serial.println("🗑 Wi-Fi credentials deleted from SD Card.");
        return true;
    } else {
        Serial.println("⚠ No Wi-Fi credentials found on SD Card to delete.");
        return false;
    }
}

// 🔹 Save User ID to SD Card
bool saveUserIdToSD(const String& userId) {
    File file = SD.open("/user_id.txt", FILE_WRITE);
    if (file) {
        file.println(userId);
        file.close();
        Serial.println("✅ User ID saved to SD Card.");
        return true;
    } else {
        Serial.println("❌ Failed to save User ID to SD Card!");
        return false;
    }
}

// 🔹 Get User ID from SD Card
String getUserIdFromSD() {
    File file = SD.open("/user_id.txt", FILE_READ);
    if (file) {
        String userId = file.readStringUntil('\n');
        userId.trim();
        file.close();
        Serial.println("✅ User ID loaded from SD Card: " + userId);
        return userId;
    } else {
        Serial.println("❌ No User ID found on SD Card!");
        return "";
    }
}

// 🔹 Delete User ID from SD Card
bool removeUserIdFromSD() {
  if (!SD.begin(SD_CS)) {
    Serial.println("⚠️ SD Card not initialized!");
    return false;
  }

  if (SD.exists("/userId.txt")) {
    SD.remove("/userId.txt");
    Serial.println("🗑️ User ID removed from SD card!");
    return true;
  } else {
    Serial.println("⚠️ No User ID found on SD card!");
    return false;
  }
}


// 🔹 Save Device ID to SD Card
bool saveDeviceIdToSD(const String& deviceId) {
    File file = SD.open("/device_id.txt", FILE_WRITE);
    if (file) {
        file.println(deviceId);
        file.close();
        Serial.println("✅ Device ID saved to SD Card.");
        return true;
    } else {
        Serial.println("❌ Failed to save Device ID to SD Card!");
        return false;
    }
}

// 🔹 Get Device ID from SD Card
String getDeviceIdFromSD() {
    File file = SD.open("/device_id.txt", FILE_READ);
    if (file) {
        String deviceId = file.readStringUntil('\n');
        deviceId.trim();
        file.close();
        Serial.println("✅ Device ID loaded from SD Card: " + deviceId);
        return deviceId;
    } else {
        Serial.println("❌ No Device ID found on SD Card!");
        return "";
    }
}

// 🔹 Save Measurement Duration to SD Card
bool saveDurationToSD(int duration) {
    File file = SD.open("/duration.txt", FILE_WRITE);
    if (file) {
        file.println(duration);
        file.close();
        Serial.println("✅ Measurement duration saved to SD Card.");
        return true;
    } else {
        Serial.println("❌ Failed to save measurement duration to SD Card!");
        return false;
    }
}

// 🔹 Get Measurement Duration from SD Card
int getDurationFromSD() {
    File file = SD.open("/duration.txt", FILE_READ);
    if (file) {
        String durationStr = file.readStringUntil('\n');
        file.close();
        Serial.println("✅ Measurement duration loaded from SD Card: " + durationStr);
        return durationStr.toInt();
    } else {
        Serial.println("❌ No measurement duration found on SD Card!");
        return -1; // Return -1 if no value is found
    }
}

// 🔹 Save counter to SD card
bool saveCounterToSD(int counter) {
  if (!SD.begin(SD_CS)) {
    Serial.println("⚠️ SD Card not initialized!");
    return false;
  }

  File file = SD.open("/counter.txt", FILE_WRITE);
  if (!file) {
    Serial.println("⚠️ Failed to open counter file for writing!");
    return false;
  }

  file.println(counter);
  file.close();
  return true;
}

// 🔹 Read counter from SD card
int getCounterFromSD() {
  if (!SD.begin(SD_CS)) {
    Serial.println("⚠️ SD Card not initialized!");
    return 0;
  }

  File file = SD.open("/counter.txt");
  if (!file) {
    Serial.println("⚠️ Counter file not found, starting from 1!");
    return 1; // Default start from 1
  }

  int counter = file.parseInt();
  file.close();
  return counter;
}
