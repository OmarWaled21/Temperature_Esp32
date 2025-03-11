#ifndef SD_MODULE_H
#define SD_MODULE_H

#include <SD.h>
#include <SPI.h>

// Configuration structure
struct SD_Config  {
  int csPin = 5;
  int misoPin = 26;
  int mosiPin = 25;
  int sckPin = 33;
  const char* filename = "/data.csv";
};

// Initialize with custom configuration
bool SD_init(SD_Config config);

// Data logging functions
void SD_appendData(const String &timestamp, float temperature, float humidity);

#endif