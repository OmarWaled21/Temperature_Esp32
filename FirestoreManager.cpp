#include "RTC.h"
#include "WebServerManager.h"
#include <FirestoreManager.h>
#include <WiFiClientSecure.h>
#include <WiFiManager.h>
#include <Utilities.h>
#include <Globals.h>

// Firebase Configuration
const char* FIREBASE_URL = "https://firestore.googleapis.com/v1/projects/tomatiki-temperature/databases/(default)/documents";
const char* API_KEY = "AIzaSyAW79tOn7YE8FfW7reY_mUliJ1_NjMjI38";

// Function to send data to Firestore
void sendTemperatureToFirestore(float temperature, float humidity) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("❌ WiFi not connected! Cannot send data.");
    return;
  }

  String userId = getStringPreference("user", "user_id");
  String deviceId = getStringPreference("user", "device_id");
  
  if (userId.isEmpty() || deviceId.isEmpty()) {
    Serial.println("❌ Error: User ID or Device ID is missing!");
    return;
  }

  HTTPClient http;
  WiFiClientSecure client;
  client.setInsecure();  // Skip SSL verification (not recommended for production)

  // Firestore API endpoint for temperatures subcollection
  String url = String(FIREBASE_URL) + "/users_admin/" + userId + "/devices/" + deviceId + "/temperatures?key=" + API_KEY;

  // Get the current timestamp in ISO 8601 format
  String timestamp = RTCTimestamp();
  if (timestamp == "") {
    Serial.println("❌ Error: Failed to get timestamp");
    return;
  }

  // JSON Payload
  StaticJsonDocument<200> doc;
  doc["fields"]["temp"]["doubleValue"] = temperature;
  doc["fields"]["humidity"]["doubleValue"] = humidity;
  doc["fields"]["time"]["timestampValue"] = timestamp;  // Use actual timestamp function

  String jsonData;
  serializeJson(doc, jsonData);

  // HTTP POST Request
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(jsonData);
  if (httpResponseCode > 0) {
    Serial.print("✅ Sent to Firestore. Response: ");
    Serial.println(http.getString());
  } else {
    Serial.print("❌ Failed. Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}

int getDeviceDuration() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("❌ WiFi not connected! Cannot fetch duration.");
    return -1;
  }

  String userId = getStringPreference("user", "user_id");
  String deviceId = getStringPreference("user", "device_id");

  if (userId.isEmpty() || deviceId.isEmpty()) {
    Serial.println("❌ Error: User ID or Device ID is missing!");
    return -1;
  }

  HTTPClient http;
  WiFiClientSecure client;
  client.setInsecure();  // Skip SSL verification

  // Firestore API endpoint to get device details
  String url = String(FIREBASE_URL) + "/users_admin/" + userId + "/devices/" + deviceId + "?key=" + API_KEY;

  http.begin(client, url);
  int httpResponseCode = http.GET();

  if (httpResponseCode == 404) {
    Serial.println("❌ Document not found. Resetting WiFi and clearing credentials.");
    // Call your function to clear stored WiFi credentials
    handleReset();
    // Optionally, disconnect WiFi and restart the device
    WiFi.disconnect(true);
    ESP.restart();
    http.end();
    return -1;
  }
  
  if (httpResponseCode > 0) {
    String payload = http.getString();
    // Serial.println("📥 Firestore Response: " + payload);

    StaticJsonDocument<300> doc;
    DeserializationError error = deserializeJson(doc, payload);

    if (error) {
      Serial.println("❌ JSON Parsing Error!");
      http.end();
      return -1;
    }

    // Extract duration value
    if (doc["fields"]["duration"]["integerValue"]) {
      int duration = doc["fields"]["duration"]["integerValue"];
      Serial.print("✅ Retrieved Duration: ");
      Serial.println(duration);

      // Save duration to preferences
      saveIntPreference("user", "duration", duration);
      Serial.println("💾 Duration saved in preferences.");

      http.end();
      return duration;
    } else {
      Serial.println("❌ Error: Duration field missing!");
    }
  } else {
    Serial.print("❌ HTTP Request Failed. Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
  return -1;
}