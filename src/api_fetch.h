#ifndef API_FETCH_H
#define API_FETCH_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

extern float eventTime;
extern bool leg1Load;
extern bool leg2Load;
extern bool leg3Load;
extern bool leg4Load;
extern const char* currentLoad;
extern bool toolLoaded;
extern bool loadedToHub;

void fetchDataTask(void *pvParameters);
void ParseAPIResponse(const String& jsonResponse);

extern String apiURL;

#endif // API_FETCH_H
