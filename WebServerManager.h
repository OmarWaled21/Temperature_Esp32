#ifndef WEBSERVERMANGER
#define WEBSERVERMANGER

#include <WebServer.h>
#include <Utilities.h>
#include <SD_Module.h>

// Add SD card handler declaration
void addSDCardHandler(const char* csvPath);

void startWebServer();
void handleWebServer();
void handleReset();

#endif