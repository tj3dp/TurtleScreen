#ifndef API_FETCH_H
#define API_FETCH_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "moonraker.h"
#include "debug.hpp"

extern float eventTime;

#define NUM_LEGS    12   // TODO: support dynamic number of legs/lanes
extern bool legLoad[NUM_LEGS];
extern int  legLane[NUM_LEGS];
extern int  legMapTool[NUM_LEGS];

extern const char* currentLoad;
extern char currentLoadBuffer[32];
extern bool toolLoaded;
extern bool loadedToHub;
extern bool currentLoadChanged;
extern int numUnits;
extern int numLanes;

void fetchDataTask(void *pvParameters);
void ParseAPIResponse(const String& jsonResponse);
extern  HTTPClient http;

extern String apiURL;
extern TaskHandle_t apiFetchTaskHandle;
extern uint32_t lastApiUpdate;

#endif // API_FETCH_H
