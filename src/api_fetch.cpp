#include "api_fetch.h"

String apiURL;
float eventTime;
bool leg1Load;
bool leg2Load;
bool leg3Load;
bool leg4Load;
const char *currentLoad;
bool toolLoaded;
bool loadedToHub;
bool currentLoadChanged;
char currentLoadBuffer[32] = "";
uint32_t lastApiUpdate;
HTTPClient http;

void fetchDataTask(void *pvParameters)
{
    while (true)
    {
        if (WiFi.status() == WL_CONNECTED && !apiURL.isEmpty())
        {
#ifdef DEBUGOUTPUT
            DEBUG_PRINT("Trying to grab API data \n");
#endif
            http.begin(apiURL);
            int httpResponseCode = http.GET();

            if (httpResponseCode == 200)
            {
                String payload = http.getString();
#ifdef DEBUGOUTPUT
                DEBUG_PRINTLN("Received data:");
                DEBUG_PRINTLN(payload);
#endif
                // Parse JSON data
                ParseAPIResponse(payload);
            }
            else
            {
                DEBUG_PRINT("HTTP error: ");
                DEBUG_PRINTLN(httpResponseCode);
            }
            http.end();
            moonraker.get_printer_ready();
            if(!moonraker.unready){
                moonraker.get_AFC_status();
                moonraker.get_printer_info();
                if(moonraker.data.printing)
                {
                    moonraker.get_progress();
                }
            }
        }
        else
        {
            DEBUG_PRINTLN("Wi-Fi not connected or API URL not set");
        }
        lastApiUpdate = xTaskGetTickCount();
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void ParseAPIResponse(const String &jsonResponse)
{
#ifdef DEBUGOUTPUT
    DEBUG_PRINTLN("Running API Parse");
#endif
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, jsonResponse);

    if (error)
    {
        DEBUG_PRINT("Failed to parse JSON: ");
        DEBUG_PRINTLN(error.f_str());
        return;
    }

    JsonObject result = doc["result"];
    eventTime = result["eventtime"];
    JsonObject status = result["status"];
    JsonObject afc = status["AFC"];

#ifdef DEBUGOUTPUT
    DEBUG_PRINT("Turtle_1 Object: ");
    DEBUG_PRINTLN(afc["Turtle_1"].as<String>());
#endif
    for (int leg = 1; leg <= 4; ++leg)
    {
        String legKey = "leg" + String(leg);
        if (afc.containsKey("Turtle_1") && afc["Turtle_1"].containsKey(legKey.c_str()))
        {
            JsonObject legData = afc["Turtle_1"][legKey];
            bool load = legData["load"];
            bool prep = legData["prep"];
            loadedToHub = legData["loaded_to_hub"];
            int lane = legData["LANE"];
#ifdef DEBUGOUTPUT
            DEBUG_PRINT("Lane ");
            DEBUG_PRINT(lane);
            DEBUG_PRINT(" - Load: ");
            DEBUG_PRINT(load ? "true" : "false");
            DEBUG_PRINT(", Prep: ");
            DEBUG_PRINT(prep ? "true" : "false");
            DEBUG_PRINT(", Loaded to Hub: ");
            DEBUG_PRINTLN(loadedToHub ? "true" : "false");
#endif
            if (lane == 1)
            {
                leg1Load = load;
            }
            else if (lane == 2)
            {
                leg2Load = load;
            }
            else if (lane == 3)
            {
                leg3Load = load;
            }
            else if (lane == 4)
            {
                leg4Load = load;
            }
        }
        else
        {
            DEBUG_PRINT("Checking key: ");
            DEBUG_PRINTLN(legKey);
            DEBUG_PRINTLN("Key not found.");
        }
    }

    if (status.containsKey("AFC"))
    {
        JsonObject afcStatus = status["AFC"];

        if (afcStatus.containsKey("system"))
        {
            JsonObject system = afcStatus["system"];

#ifdef DEBUGOUTPUT
            DEBUG_PRINT("System Object: ");
            serializeJson(system, Serial);
            DEBUG_PRINTLN();
#endif
            currentLoadChanged = false;
            currentLoad = system["current_load"].as<const char *>();

            if (currentLoad == nullptr)
            {
                if (currentLoadBuffer[0] != '\0')
                {
                    currentLoadBuffer[0] = '\0';
                    currentLoadChanged = true;
                }
            }
            else
            {
                if (strcmp(currentLoadBuffer, currentLoad) != 0)
                {
                    strncpy(currentLoadBuffer, currentLoad, sizeof(currentLoadBuffer) - 1);
                    currentLoadBuffer[sizeof(currentLoadBuffer) - 1] = '\0';
                    currentLoadChanged = true;
                    //
                }
            }

            toolLoaded = system["tool_loaded"];
            loadedToHub = system["hub_loaded"];

#ifdef DEBUGOUTPUT
            DEBUG_PRINT("Raw tool_loaded value: ");
            DEBUG_PRINTLN(toolLoaded ? "true" : "false");
#endif
            JsonVariant buffer = system["buffer"];
#ifdef DEBUGOUTPUT
            DEBUG_PRINT("Buffer: ");
            if (buffer.isNull())
            {
                DEBUG_PRINTLN("null");
            }
            else
            {
                DEBUG_PRINTLN(buffer.as<String>());
            }
#endif
        }
        else
        {
            DEBUG_PRINTLN("System key not found in AFC.");
        }
    }
    else
    {
        DEBUG_PRINTLN("AFC key not found in status.");
    }
#ifdef DEBUGOUTPUT
    DEBUG_PRINT("Lane 1 Status: ");
    DEBUG_PRINTLN(leg1Load);
    DEBUG_PRINT("Lane 2 Status: ");
    DEBUG_PRINTLN(leg2Load);
    DEBUG_PRINT("Lane 3 Status: ");
    DEBUG_PRINTLN(leg3Load);
    DEBUG_PRINT("Lane 4 Status: ");
    DEBUG_PRINTLN(leg4Load);
    DEBUG_PRINT("Tool Status: ");
    DEBUG_PRINTLN(toolLoaded ? "true" : "false");
    DEBUG_PRINT("Hub Status: ");
    DEBUG_PRINTLN(loadedToHub ? "true" : "false");
    DEBUG_PRINT("Current Load: ");
    DEBUG_PRINTLN(currentLoad);
#endif
}
