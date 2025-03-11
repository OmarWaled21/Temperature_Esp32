#include "RTC.h"

// تهيئة كائن RTC
RTC_DS3231 rtc;

void setupRTC() {
  // تهيئة RTC
  Wire.begin(21, 22);  // تخصيص SDA و SCL في ESP32
  if (!rtc.begin()) {
    Serial.println("⛔ لم يتم العثور على وحدة RTC!");
    while (1);
  }
}

DateTime RTCNow() {
  // قراءة الوقت والتاريخ من DS3231
  return rtc.now();
}

// تحويل الوقت إلى سلسلة نصية بصيغة ISO 8601
String RTCNowString() {
  DateTime now = RTCNow();
  char timestamp[30];
  sprintf(timestamp, "%04d-%02d-%02dT%02d:%02d:%02dZ",
          now.year(), now.month(), now.day(),
          now.hour(), now.minute(), now.second());
  return String(timestamp);
}