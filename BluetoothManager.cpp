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

      if (saveWiFiCredentialsToSD(ssid, password)) {
        SerialBT.println("✅ Credentials saved to SD Card. Restarting...");
        delay(2000);
        ESP.restart();
      } else {
        SerialBT.println("❌ Failed to save Wi-Fi credentials to SD Card.");
      }
    } else if (data == "RESET") {
      SerialBT.println("⚠ Resetting Wi-Fi credentials...");
      if (clearWiFiCredentialsFromSD()) {
        SerialBT.println("✅ Wi-Fi credentials cleared.");
      } else {
        SerialBT.println("⚠ No Wi-Fi credentials to delete.");
      }
    } else {
      SerialBT.println("❌ Invalid format. Use: SSID:<ssid>PASS:<password>");
    }
  }
}

void initBtSerial() {
  SerialBT.begin("ESP32_Config");
  Serial.println("\n===== ESP32 Initialization =====");
}