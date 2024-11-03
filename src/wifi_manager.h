#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Preferences.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>
#include "api_fetch.h"


extern const char* apSSID;          // SSID for AP
extern const char* apPassword;      // Password for AP
extern Preferences preferences;      // Extern declaration
extern AsyncWebServer server;        // Extern declaration



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