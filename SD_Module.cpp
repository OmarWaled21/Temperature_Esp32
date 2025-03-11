#include "SD_Module.h"

namespace {
  SD_Config current_config; // Changed from sd_config to current_config
  SPIClass* spi = nullptr;
}

bool SD_init(SD_Config config) {
  current_config = config; // Use current_config instead of sd_config
  
  spi = new SPIClass((config.csPin == 5) ? HSPI : VSPI);
  spi->begin(config.sckPin, config.misoPin, config.mosiPin, config.csPin);

  if (!SD.begin(config.csPin, *spi)) {
    Serial.println("❌ SD Card failed!");
    return false;
  }

  if (!SD.exists(config.filename)) {
    File file = SD.open(config.filename, FILE_WRITE);
    if (file) {
      file.println("Date,Temperature,Humidity");
      file.close();
    }
  }
  
  Serial.println("✅ SD Card ready");
  return true;
}

void SD_appendData(const String &timestamp, float temperature, float humidity) {
  File file = SD.open(current_config.filename, FILE_APPEND); // Use current_config
  if (file) {
    file.print(timestamp);
    file.print(',');
    file.print(temperature);
    file.print(',');
    file.println(humidity);
    file.close();
  }
}