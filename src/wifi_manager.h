#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>
#include "api_fetch.h"


extern const char* apSSID;
extern const char* apPassword;
extern AsyncWebServer server;

void setupWiFiAP();
void connectToWiFiTask(void *pvParameters);
void loadCredentials();
void saveCredentials(const String& ssid, const String& password, const String& host);

extern String targetSSID;
extern String targetPassword;
extern String targetSSID;
extern String targetPassword;
extern String targetHost;
extern String apiURL;



#endif // WIFI_MANAGER_H