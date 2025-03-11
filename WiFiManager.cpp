#include <WiFi.h>
#include <BluetoothSerial.h>
#include <Globals.h>
#include <WebServerManager.h>

const int MAX_CONNECTION_ATTEMPTS = 15;
const int UDP_PORT = 12345;

void clearWifiCredentials() {
  Serial.println("⚠ Clearing Wi-Fi credentials...");
  clearWiFiCredentialsFromSD(); // Clear credentials from SD card
  WiFi.disconnect(true, true);  // Clear Wi-Fi settings from ESP32's NVS
  delay(500);
  Serial.println("\n🚀 Restarting ESP32...");
  ESP.restart();
}

void activateBluetooth() {
  if (!SerialBT.hasClient()) {
    SerialBT.begin("ESP32_Config"); // Start Bluetooth with a device name
    Serial.println("🔵 Bluetooth activated for configuration");
  }
}

void connectToWiFi() {
  Serial.println("\n📶 Calling connectToWiFi()...");

  String savedSSID, savedPassword;
  bool credentialsLoaded = loadWiFiCredentialsFromSD(savedSSID, savedPassword);
  Serial.printf("📂 Credentials Loaded: %d | SSID: %s | Password: %s\n", credentialsLoaded, savedSSID.c_str(), savedPassword.c_str());

  if (savedSSID.length() > 0) {
    Serial.println("\n📡 Found saved Wi-Fi credentials");
    WiFi.begin(savedSSID.c_str(), savedPassword.c_str());

    Serial.print("⏳ Connecting to WiFi");
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < MAX_CONNECTION_ATTEMPTS) {
      delay(1000);
      Serial.print(".");
      attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\n✅ WiFi connected");
      Serial.print("🌐 IP Address: ");
      Serial.println(WiFi.localIP());

      // Initialize network services
      if (udp.begin(UDP_PORT)) {
        Serial.println("UDP service started");
      } else {
        Serial.println("Failed to start UDP service");
      }

      // Deactivate Bluetooth if active
      if (SerialBT.hasClient()) {
        SerialBT.end();
        Serial.println("🔵 Bluetooth deactivated");
      }

      startWebServer(); // Start the web server
    } else {
      Serial.println("\n❌ Failed to connect to WiFi");
      activateBluetooth(); // Fallback to Bluetooth
    }
  } else {
    Serial.println("\n🔵 No saved Wi-Fi credentials");
    activateBluetooth(); // Fallback to Bluetooth
  }
}