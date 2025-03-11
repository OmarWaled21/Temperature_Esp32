#ifndef RTC_H
#define RTC_H

#include <Wire.h>
#include <RTClib.h>

void setupRTC();
DateTime RTCNow();
String RTCNowString();

#endif