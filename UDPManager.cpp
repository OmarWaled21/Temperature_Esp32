#include <UDPManager.h>
#include <WiFi.h>
#include <Globals.h>

const int UDP_PORT = 12345;

void initUDP() {
  if (udp.begin(UDP_PORT)) {
    Serial.println("UDP service started");
  } else {
    Serial.println("Failed to start UDP service");
  }
}

void handleUDP() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    char packetBuffer[255];
    int len = udp.read(packetBuffer, sizeof(packetBuffer));
    if (len > 0) {
      packetBuffer[len] = '\0';
      String request(packetBuffer);

      if (request.startsWith("DISCOVER_ESP32")) {
        IPAddress ip = WiFi.localIP();
        String response = "ESP32_IP:" + ip.toString();
        udp.beginPacket(udp.remoteIP(), udp.remotePort());
        udp.print(response);
        udp.endPacket();
        Serial.println("UDP request handled");
      }
    }
  }
}