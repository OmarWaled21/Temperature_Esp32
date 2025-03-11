#include <WiFiManager.h>
#include <BluetoothManager.h>
#include <WebServerManager.h>
#include <FirestoreManager.h>
#include <Utilities.h>
#include <UDPManager.h>
#include <temperature_sensor.h>
#include <RTC.h>
#include <LCD.h>
#include <Globals.h>

void setup() {
  Serial.begin(115200);

  setupRTC();

  // 🔹 Initialize SD Card
  if (!initSDCard()) {
    Serial.println("⚠ SD Card unavailable, skipping operations.");
    return;
  }

  initBtSerial();
  
  delay(500);
  
  initLcd();
  
  delay(500);

  connectingWiFiLcd();

  delay(500);
  
  connectToWiFi();
 

  connectedToWiFiLcd();

  sensorSetUp();
  delay(500);
  initUDP();

  delay(2000);
  lcdClear();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    handleWebServer();
    handleUDP();

    // Simulate temperature readings
    String userId = getUserIdFromSD();
    String deviceId = getDeviceIdFromSD();

    Serial.print("User ID: ");
    Serial.println(userId);
    Serial.println(deviceId);

    showUserAndDeviceIdLcd(userId,deviceId);

    // If userId not found, start a timer and call handleReset() after 1 minute
    static unsigned long userIdNotFoundStart = 0;
    if (userId.length() == 0) {
      if (userIdNotFoundStart == 0) {
        // Start the timer when userId is first detected as empty
        userIdNotFoundStart = millis();
      } else if (millis() - userIdNotFoundStart >= 60000) {
        Serial.println("❌ User ID not found for 1 minute, resetting Wi-Fi credentials...");
        
        noUserIdLcd();
        delay(2000);

        handleReset();
        // Reset timer after calling handleReset
        userIdNotFoundStart = 0;
      }
    } else {
      // Reset timer if userId becomes available
      userIdNotFoundStart = 0;

      float temperature = roundf(measureTemperatureSensor() * 10) / 10;  // Replace with actual sensor data
      float humidity = random(40, 60);

      sendTemperatureToFirestore(temperature, humidity);

      showDataLcd(temperature, humidity);

      int durationMinutes = getDeviceDuration();
      int durationMillis = durationMinutes * 60 * 1000;  // Convert to milliseconds

      String now = RTCNowString();

      Serial.printf("%s\n", now.c_str());

      delay(durationMillis);
    }
    delay(500);
  } else {
    handleBluetoothData();
  }
}