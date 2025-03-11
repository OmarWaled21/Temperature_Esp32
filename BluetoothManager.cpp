#include <BluetoothManager.h>
#include <WiFiManager.h>
#include <Globals.h>

void handleBluetoothData() {
  if (SerialBT.available()) {
    String data = SerialBT.readStringUntil('\n');
    data.trim();

    if (data.startsWith("SSID:") && data.indexOf("PASS:") != -1) {
      int passIndex = data.indexOf("PASS:");
      String ssid = data.substring(5, passIndex);
      String password = data.substring(passIndex + 5);

      Serial.println("\n📡 Received Wi-Fi credentials:");
      Serial.println("SSID: " + ssid);
      Serial.println("Password: " + password);

      saveStringPreference("wifi", "ssid", ssid);
      saveStringPreference("wifi", "password", password);

      SerialBT.println("✅ Credentials saved. Restarting...");
      delay(2000);
      ESP.restart();
    } else if (data == "RESET") {
      SerialBT.println("⚠ Resetting Wi-Fi credentials...");
      clearWifiCredentials();
    } else {
      SerialBT.println("❌ Invalid format. Use: SSID:<ssid>PASS:<password>");
    }
  }
}

void initBtSerial() {
  if (isBlueToothActivate) return; // Prevent reinitialization

  if (!SerialBT.begin("ESP32_Config")) {
    Serial.println("❌ Bluetooth initialization failed");
  } else {
    isBlueToothActivate = true; // Update global flag
    Serial.println("\n===== ESP32 Initialization =====");
  }
}

void checkBluetoothHealth() {
  if (!isBlueToothActivate && SerialBT.available()) {
    Serial.println("🔄 Reinitializing Bluetooth...");
    SerialBT.end();
    delay(200);
    initBtSerial();
  }
}

void activateBluetooth() {
  if (!isBlueToothActivate) {
    SerialBT.begin("ESP32_Config");
    isBlueToothActivate = true;
    Serial.println("🔵 Bluetooth activated");
  }
}
