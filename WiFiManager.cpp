#include "UDPManager.h"
#include <WiFiManager.h>
#include <Globals.h>
#include <WebServerManager.h>

const int MAX_CONNECTION_ATTEMPTS = 15;
const int UDP_PORT = 12345;

void clearWifiCredentials() {
  removePreference("wifi", "ssid");
  removePreference("wifi", "password");

  WiFi.disconnect(true, true);
  delay(500);

  Serial.println("\n🚀 Restarting ESP32...");
  ESP.restart();
}

void connectToWiFi() {
  String savedSSID = getStringPreference("wifi", "ssid");
  String savedPassword = getStringPreference("wifi", "password");

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
      initUDP();

      SerialBT.end();
      isBlueToothActivate = false;
      startWebServer();
    } else {
      Serial.println("\n❌ Failed to connect to WiFi");
      activateBluetooth();
    }
  } else {
    Serial.println("\n🔵 No saved Wi-Fi credentials");
    activateBluetooth();
  }
}