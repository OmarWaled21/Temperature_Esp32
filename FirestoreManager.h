#ifndef FIRESTOREMANAGER_H
#define FIRESTOREMANAGER_H

#include <HTTPClient.h>
#include <Utilities.h>
#include <RTC.h>

void sendTemperatureToFirestore(float temperature, float humidity);
void updateDeviceStatus(bool status);
int getDeviceDuration();

#endif