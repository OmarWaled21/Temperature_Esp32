#include <WiFiManager.h>
#include <BluetoothManager.h>
#include <WebServerManager.h>
#include <FirestoreManager.h>
#include <Utilities.h>
#include <UDPManager.h>
#include <temperature_sensor.h>
#include <Globals.h>
#include <RTC.h>
#include <LCD.h>

void setup() {
  Serial.begin(115200);

  // 🔹 Initialize LCD
  initLcd();

  // Initialize RTC module
  initRTC();

  // Check for existing credentials before initializing Bluetooth
  bool hasCredentials = getStringPreference("wifi", "ssid").length() > 0;

  // Only initialize Bluetooth if no credentials exist
  if (!hasCredentials) {
    initBtSerial();
    connectingWiFiLcd();
  }

  // Set up the temperature sensor (replace this with your actual sensor setup)
  sensorSetUp();

  // Connect to Wi-Fi
  connectToWiFi();

  if (WiFi.status() == WL_CONNECTED) {
    connectedToWiFiLcd();  // Show Wi-Fi connected message on LCD
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    handleWebServer();
    handleUDP();

    // Simulate temperature readings
    String userId = getStringPreference("user", "user_id");
    String deviceId = getStringPreference("user", "device_id");

    Serial.print("User ID: ");
    Serial.println(userId);
    Serial.println(deviceId);

    // If userId not found, start a timer and call handleReset() after 1 minute
    static unsigned long userIdNotFoundStart = 0;
    if (userId.length() == 0) {
      if (userIdNotFoundStart == 0) {
        // Start the timer when userId is first detected as empty
        userIdNotFoundStart = millis();
        noUserIdLcd();  // Show "No User ID" on LCD
      } else if (millis() - userIdNotFoundStart >= 60000) {
        Serial.println("❌ User ID not found for 1 minute, resetting Wi-Fi credentials...");
        handleReset();
        // Reset timer after calling handleReset
        userIdNotFoundStart = 0;
      }
    } else {
      // Reset timer if userId becomes available
      userIdNotFoundStart = 0;
      showUserAndDeviceIdLcd(userId, deviceId);  // Display user and device ID on LCD

      float temperature = roundf(measureTemperatureSensor() * 10) / 10;  // Replace with actual sensor data
      float humidity = random(40, 60);

      sendTemperatureToFirestore(temperature, humidity);

      // 🔹 Display data on LCD
      showDataLcd(temperature, humidity);

      int durationMinutes = getDeviceDuration();
      int durationMillis = durationMinutes * 60 * 1000;  // Convert to milliseconds

      // Print the next reading duration to the serial monitor
      Serial.printf("⏳ Next reading in %d minutes...\n", durationMinutes);

      delay(durationMillis);
    }
    delay(500);
  } else {
    checkBluetoothHealth();
    handleBluetoothData();
  }
}