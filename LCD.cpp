#include <LCD.h>

// إعداد شاشة LCD (العنوان 0x27، الحجم 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void initLcd() {

  // 🔹 تهيئة شاشة LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
}

void connectingWiFiLcd() {
  // 🔹 Initialize Wi-Fi
  lcd.setCursor(0, 1);
  lcd.print("Connecting WiFi...");
}

void connectedToWiFiLcd() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected!");
}

void lcdClear() {
  lcd.clear();
}

void showUserAndDeviceIdLcd(String userId, String deviceId) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("User: ");
  lcd.print(userId.length() > 0 ? userId : "N/A");

  lcd.setCursor(0, 1);
  lcd.print("Device: ");
  lcd.print(deviceId.length() > 0 ? deviceId : "N/A");
}

void noUserIdLcd() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("No User ID!");
  lcd.setCursor(0, 1);
  lcd.print("Resetting WiFi...");
}

void showDataLcd(float temperature, int humidity) {
  // عرض البيانات على شاشة LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(roundf(temperature * 10) / 10);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");
}
