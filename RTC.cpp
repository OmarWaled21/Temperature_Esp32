#include <RTC.h>

// Create an RTC instance
RTC_DS3231 rtc;

void initRTC() {
    Wire.begin();
    
    if (!rtc.begin()) {
        Serial.println("❌ RTC module not found!");
        return;
    }

    if (rtc.lostPower()) {
        Serial.println("⚠ RTC lost power, setting to compile time...");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set time to compilation time
    }
}

String RTCTimestamp() {
    DateTime now = rtc.now(); // Get RTC time (assumed to be in local time)

    // ✅ Convert Egypt time (UTC+2) to UTC before saving
    now = now.unixtime() - (10 *60 - 42);  // Subtract 2 hours to get UTC

    DateTime utcTime = DateTime(now);

    char timeString[30];
    snprintf(timeString, sizeof(timeString), "%04d-%02d-%02dT%02d:%02d:%02dZ",
             utcTime.year(), utcTime.month(), utcTime.day(), 
             utcTime.hour(), utcTime.minute(), utcTime.second());

    return String(timeString);
}
