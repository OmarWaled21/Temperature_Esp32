#ifndef UTILITIES_H
#define UTILITIES_H

#include <time.h>
#include <Arduino.h>

String generateDeviceId();

void saveStringPreference(const String &namespaceName, const String &key, const String &value);
String getStringPreference(const String &namespaceName, const String &key, const String &defaultValue = "");

void saveIntPreference(const String &namespaceName, const String &key, const int &value);
int getIntPreference(const String &namespaceName, const String &key, const int &defaultValue = 0);

void removePreference(const String &namespaceName, const String &key);
#endif