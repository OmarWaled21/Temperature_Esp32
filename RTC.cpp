#include <RTC.h>

// Create an RTC instance
RTC_DS3231 rtc;

void initRTC() {
  Wire.begin();
  Serial.println("✅ RTC module initialized!");

  if (!rtc.begin()) {
    Serial.println("❌ RTC module not found!");
    return;
  }

  if (rtc.lostPower()) {
    Serial.println("⚠ RTC lost power, setting to compile time...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // Set time to compilation time
  }
}

String RTCTimestamp() {
  DateTime now = rtc.now();  // Get RTC time (assumed to be in local time)

  // Add 9 minutes and 42 seconds to compensate for drift
  time_t adjustedTime = now.unixtime() + (9 * 60) + 42;  // Add 582 seconds
  
  // Convert Egypt time (UTC+2) to UTC
  adjustedTime -= 2 * 3600;  // Subtract 2 hours
  
  DateTime utcTime = DateTime(adjustedTime);

  char timeString[30];
  snprintf(timeString, sizeof(timeString), "%04d-%02d-%02dT%02d:%02d:%02dZ",
           utcTime.year(), utcTime.month(), utcTime.day(),
           utcTime.hour(), utcTime.minute(), utcTime.second());

  return String(timeString);
}
