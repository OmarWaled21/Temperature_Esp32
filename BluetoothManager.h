#ifndef BLUETOOTHMANAGER_H
#define BLUETOOTHMANAGER_H

#include <BluetoothSerial.h>
#include <Utilities.h>

void handleBluetoothData();
void initBtSerial();
void checkBluetoothHealth();
void activateBluetooth();

#endif