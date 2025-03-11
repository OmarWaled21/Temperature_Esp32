#ifndef RTC_H
#define RTC_H

#include <Wire.h>
#include <RTClib.h>

extern RTC_DS3231 rtc; // Declare RTC object globally

void initRTC();           // Function to initialize RTC
String RTCTimestamp(); // Function to get RTC timestamp

#endif