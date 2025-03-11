#include <WebServerManager.h>
#include <Globals.h>
#include <WiFiManager.h>
#include <Utilities.h>

WebServer server(80);
const char* sd_csv_path = nullptr;

void startWebServer() {
  // Configure server routes
  server.on("/", []() {
    server.send(200, "text/html",
                "<h1>ESP32 Wi-Fi Server</h1>"
                "<p>Connected to Wi-Fi!</p>"
                "<button onclick=\"fetch('/userid')\">Get User Id</button>"
                "<button onclick=\"fetch('/reset')\">Reset Wi-Fi</button>"
                "<button onclick=\"window.location.href='/data.csv'\">Download Data</button>");

  });

  server.on("/reset", handleReset);

  server.on("/deviceid", HTTP_GET, []() {
    String deviceId = generateDeviceId();
    server.send(200, "text/plain", deviceId);
    Serial.printf("Served device ID: %s\n", deviceId.c_str());
  });

  server.on("/userid", HTTP_POST, []() {
    if (server.hasArg("plain")) {
      String userId = server.arg("plain");
      Serial.printf("📥 Received User ID: %s\n", userId.c_str());

      saveStringPreference("user", "user_id", userId);

      // تأكيد الحفظ
      String checkUserId = getStringPreference("user", "user_id");
      Serial.printf("✅ Saved User ID: %s\n", checkUserId.c_str());

      server.send(200, "text/plain", "User ID saved");
    } else {
      server.send(400, "text/plain", "Missing user ID");
    }
  });

  if (sd_csv_path) {
    server.on("/data.csv", HTTP_GET, []() {
      File dataFile = SD.open(sd_csv_path);
      if (dataFile) {
        server.sendHeader("Content-Type", "text/csv");
        server.sendHeader("Content-Disposition", "attachment; filename=data.csv");
        server.streamFile(dataFile, "text/csv");
        dataFile.close();
      } else {
        server.send(500, "text/plain", "Error reading data file");
      }
    });
  }

  server.onNotFound([]() {
    server.send(404, "text/plain", "Endpoint not found");
  });

  server.begin();
  Serial.println("🌍 Web server started");
}

void handleWebServer() {
  server.handleClient();
}

void handleReset() {
  removePreference("user", "user_id");

  server.send(200, "text/html", "<h1>Wi-Fi Resetting...</h1><p>ESP32 will restart.</p>");
  delay(2000);
  clearWifiCredentials();
}

void addSDCardHandler(const char* csvPath) {
  sd_csv_path = csvPath;
}