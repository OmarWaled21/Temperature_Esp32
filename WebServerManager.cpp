#include <WebServerManager.h>
#include <Globals.h>
#include <WiFiManager.h>
#include <Utilities.h>

WebServer server(80);

void startWebServer() {
  // Configure server routes
  server.on("/", []() {
    server.send(200, "text/html",
                "<h1>ESP32 Wi-Fi Server</h1>"
                "<p>Connected to Wi-Fi!</p>"
                "<button onclick=\"fetch('/userid')\">Get User Id</button>"
                "<button onclick=\"fetch('/reset')\">Reset Wi-Fi</button>");
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

      saveUserIdToSD(userId);
      // تأكيد الحفظ
      String checkUserId = getUserIdFromSD();

      Serial.printf("✅ Saved User ID: %s\n", checkUserId.c_str());

      server.send(200, "text/plain", "User ID saved");
    } else {
      server.send(400, "text/plain", "Missing user ID");
    }
  });


  server.onNotFound([]() {
    server.send(404, "text/plain", "Endpoint not found");
  });

  server.begin();
  Serial.println("🌍 Web server started");
}

void handleWebServer(){
  server.handleClient();
}

void handleReset() {
  removeUserIdFromSD();


  server.send(200, "text/html", "<h1>Wi-Fi Resetting...</h1><p>ESP32 will restart.</p>");
  delay(2000);
  clearWifiCredentials();
}

