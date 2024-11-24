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
int numUnits;
int numLanes;
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

void ParseAPIResponse(const String &jsonResponse) {
#ifdef DEBUG_OUTPUT
    Serial.println("Running API Parse");
#endif
    DynamicJsonDocument doc(4096); // Adjusted size as necessary
    DeserializationError error = deserializeJson(doc, jsonResponse);

    if (error) {
        Serial.print("Failed to parse JSON: ");
        Serial.println(error.f_str());
        return;
    }

    JsonObject result = doc["result"];
    if (result.isNull()) {
        Serial.println("Result key not found in JSON.");
        return;
    }

    eventTime = result["eventtime"].as<float>();

    JsonObject status = result["status"];
    JsonObject afc = status["AFC"];
    JsonObject turtle1 = afc["Turtle_1"];

    if (!turtle1.isNull()) {
#ifdef DEBUG_OUTPUT
        Serial.print("Turtle_1 Object: ");
        serializeJson(turtle1, Serial);
        Serial.println();
#endif
        // Iterate through the legs (leg1, leg2, leg3, leg4)
        for (int leg = 1; leg <= 4; ++leg) {
            String legKey = "leg" + String(leg);
            if (turtle1.containsKey(legKey)) {
                JsonObject legData = turtle1[legKey];
                bool load = legData["load"];
                bool prep = legData["prep"];
                bool loadedToHub = legData["loaded_to_hub"];
                String material = legData["material"].as<String>();
                String spool_id = legData["spool_id"].as<String>();
                String color = legData["color"].as<String>();
                float weight = legData["weight"].as<float>();

                int lane = legData["LANE"];

#ifdef DEBUG_OUTPUT
                Serial.print("Lane ");
                Serial.print(lane);
                Serial.print(" - Load: ");
                Serial.print(load ? "true" : "false");
                Serial.print(", Prep: ");
                Serial.print(prep ? "true" : "false");
                Serial.print(", Loaded to Hub: ");
                Serial.print(loadedToHub ? "true" : "false");
                Serial.print(", Material: ");
                Serial.print(material);
                Serial.print(", Spool ID: ");
                Serial.print(spool_id);
                Serial.print(", Color: ");
                Serial.print(color);
                Serial.print(", Weight: ");
                Serial.println(weight);
#endif
                // Update leg load statuses
                switch (lane) {
                    case 1:
                        leg1Load = load;
                        break;
                    case 2:
                        leg2Load = load;
                        break;
                    case 3:
                        leg3Load = load;
                        break;
                    case 4:
                        leg4Load = load;
                        break;
                    default:
                        break;
                }
            } else {
#ifdef DEBUG_OUTPUT
                Serial.print("Checking key: ");
                Serial.println(legKey);
                Serial.println("Key not found.");
#endif
            }
        }
    } else {
#ifdef DEBUG_OUTPUT
        Serial.println("Turtle_1 key not found in AFC.");
#endif
    }

    // Parsing system information
    JsonObject system = afc["system"];
    if (!system.isNull()) {
#ifdef DEBUG_OUTPUT
        Serial.print("System Object: ");
        serializeJson(system, Serial);
        Serial.println();
#endif
        currentLoadChanged = false;
        currentLoad = system["current_load"].as<const char *>();

        if (currentLoad == nullptr) {
            if (currentLoadBuffer[0] != '\0') {
                currentLoadBuffer[0] = '\0';
                currentLoadChanged = true;
            }
        } else {
            if (strcmp(currentLoadBuffer, currentLoad) != 0) {
                strncpy(currentLoadBuffer, currentLoad, sizeof(currentLoadBuffer) - 1);
                currentLoadBuffer[sizeof(currentLoadBuffer) - 1] = '\0';
                currentLoadChanged = true;
            }
        }

        toolLoaded = system["tool_loaded"];
        bool canCut = system["can_cut"].as<bool>();
        String screen = system["screen"].as<String>();

#ifdef DEBUG_OUTPUT
        Serial.print("Raw tool_loaded value: ");
        Serial.println(toolLoaded ? "true" : "false");
        Serial.print("Can Cut: ");
        Serial.println(canCut ? "true" : "false");
        Serial.print("Screen: ");
        Serial.println(screen);
#endif
    } else {
#ifdef DEBUG_OUTPUT
        Serial.println("System key not found in AFC.");
#endif
    }

#ifdef DEBUG_OUTPUT
    Serial.print("Lane 1 Status: ");
    Serial.println(leg1Load);
    Serial.print("Lane 2 Status: ");
    Serial.println(leg2Load);
    Serial.print("Lane 3 Status: ");
    Serial.println(leg3Load);
    Serial.print("Lane 4 Status: ");
    Serial.println(leg4Load);
    Serial.print("Tool Status: ");
    Serial.println(toolLoaded ? "true" : "false");
    Serial.print("Hub Status: ");
    Serial.println(loadedToHub ? "true" : "false");
    Serial.print("Current Load: ");
    Serial.println(currentLoad);
#endif
}