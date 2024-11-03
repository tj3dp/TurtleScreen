#ifndef API_FETCH_H
#define API_FETCH_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

void fetchDataTask(void *pvParameters);
void parseApiResponse(const String& json);

extern String apiURL;

#endif // API_FETCH_H
