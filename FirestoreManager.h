#ifndef FIRESTOREMANAGER_H
#define FIRESTOREMANAGER_H

#include <HTTPClient.h>

void sendTemperatureToFirestore(float temperature, float humidity);
void updateDeviceStatus(bool status);
int getDeviceDuration();

#endif