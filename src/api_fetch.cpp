#include "api_fetch.h"

#undef DEBUG_OUTPUT_FETCH

String apiURL;
float eventTime;

bool legLoad[NUM_LEGS];
int  legColor[NUM_LEGS];
int  legLane[NUM_LEGS];
int  legMapTool[NUM_LEGS];

const char *currentLoad;
bool toolLoaded;
String extruderLaneLoaded = "-none-";
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
#ifdef DEBUG_OUTPUT_FETCH
            DEBUG_PRINT("Trying to grab API data \n");
#endif
            http.begin(apiURL);
            int httpResponseCode = http.GET();

            if (httpResponseCode == 200)
            {
                String payload = http.getString();
#ifdef DEBUG_OUTPUT_FETCH
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
            if(!moonraker.unready)
            {
                moonraker.get_printer_info();
            }
        }
        else
        {
            DEBUG_PRINTLN("Wi-Fi not connected or API URL not set");
        }
        lastApiUpdate = xTaskGetTickCount();
        vTaskDelay(pdMS_TO_TICKS(900));
    }
}

void ParseAPIResponse(const String &jsonResponse) 
{
    #ifdef DEBUG_OUTPUT_FETCH
        DEBUG_PRINTLN("Running API Parse");
    #endif
    DynamicJsonDocument doc(4096); // Adjusted size as necessary
    DeserializationError error = deserializeJson(doc, jsonResponse);

    if (error) 
    {
        DEBUG_PRINT("Failed to parse JSON: ");
        DEBUG_PRINTLN(error.f_str());
        return;
    }

    JsonObject result = doc["result"];
    if (result.isNull()) 
    {
        DEBUG_PRINTLN("Result key not found in JSON.");
        return;
    }

    eventTime = result["eventtime"].as<float>();

    JsonObject status = result["status:"];
    JsonObject afc = status["AFC"];
    JsonObject turtleUnit;
    String turtleUnitName;
    for (JsonPair kv : afc) 
    {
        turtleUnitName = kv.key().c_str();  
        turtleUnit = kv.value().as<JsonObject>();
        break; 
    }

    if (!turtleUnit.isNull()) 
    {
        #ifdef DEBUG_OUTPUT_FETCH
            DEBUG_PRINT(turtleUnitName + " Object: ");
        #endif
        // Iterate through the legs (leg1, leg2, leg3, leg4)
        for (int n = 0; n <= 3; ++n)  // try to find 4 lane keys from 'lane1' to 'lane4' - TODO: extend number of keys to find to 12
        {
            String legKey = "lane" + String(n+1);
            if (turtleUnit.containsKey(legKey)) 
            {
                JsonObject legData = turtleUnit[legKey];
                bool load = legData["load"];
                bool prep = legData["prep"];
                bool loadedToHub = legData["loaded_to_hub"];
                String material = legData["material"].as<String>();
                String spool_id = legData["spool_id"].as<String>();
                String scolor = legData["color"].as<String>();
                float weight = legData["weight"].as<float>();
                int lane = legData["lane"];
                //int ledColor = (int)strtol(legData["filament_status_led"].as<String>().replace("#", "0x").c_str(), NULL, 16);
                String sLedColor = legData["filament_status_led"].as<String>();
                sLedColor.replace("#", "0x");
                int ledColor = (int)strtol(sLedColor.c_str(), NULL, 16);
                String smap = legData["map"].as<String>();
                if((smap[0] == 'T') && (smap.length() == 2))
                    legMapTool[n] = (int)(smap[1] - '0');
                else
                    legMapTool[n] = -1; // TODO: error handling for missing mapping lane -> tool
                
                legLane[n] = lane;
                legColor[n] = ledColor;

                #ifdef DEBUG_OUTPUT_FETCH
                DEBUG_PRINT("lane ");
                DEBUG_PRINT(lane);
                DEBUG_PRINT(" - Load: ");
                DEBUG_PRINT(load ? "true" : "false");
                DEBUG_PRINT(", Prep: ");
                DEBUG_PRINT(prep ? "true" : "false");
                DEBUG_PRINT(", Loaded to Hub: ");
                DEBUG_PRINT(loadedToHub ? "true" : "false");
                DEBUG_PRINT(", Material: ");
                DEBUG_PRINT(material);
                DEBUG_PRINT(", Spool ID: ");
                DEBUG_PRINT(spool_id);
                DEBUG_PRINT(", Color: ");
                DEBUG_PRINT(scolor);
                DEBUG_PRINT(", Weight: ");
                DEBUG_PRINTLN(weight);
                #endif
                // Update leg/lane load statuses
                legLoad[n] = load;
            } else {
                DEBUG_PRINT("Checking key: ");
                DEBUG_PRINTLN(legKey);
                DEBUG_PRINTLN("Key not found.");
            }
        }

        // Parsing Turtle Unit's system information (hub_loaded, etc.)
        JsonObject turtleSystem = turtleUnit["system"];
        if (!turtleSystem.isNull()) {
            bool hubLoaded = turtleSystem["hub_loaded"].as<bool>();
            bool canCut = turtleSystem["can_cut"].as<bool>();
            String screen = turtleSystem["screen"].as<String>();
            #ifdef DEBUG_OUTPUT_FETCH
            DEBUG_PRINT("Hub Loaded: ");
            DEBUG_PRINTLN(hubLoaded ? "true" : "false");
            DEBUG_PRINT("Can Cut: ");
            DEBUG_PRINTLN(canCut ? "true" : "false");
            DEBUG_PRINT("Screen: ");
            DEBUG_PRINTLN(screen);
            #endif
            loadedToHub = hubLoaded; // Assigning hubLoaded status to toolLoaded if relevant
        }
    } 
    else 
    {
        DEBUG_PRINTLN("Unit key not found in AFC.");
    }

    // Parsing AFC system information
    JsonObject system = afc["system"];
    if (!system.isNull()) 
    {
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

        JsonObject extruder = system["extruders"]["extruder"];
        if (!extruder.isNull()) {
            toolLoaded = extruder["tool_start_sensor"].as<bool>();
            if(extruder["lane_loaded"].as<const char *>() == nullptr)
                extruderLaneLoaded = "-none-";
            else
                extruderLaneLoaded = extruder["lane_loaded"].as<String>();

            String buffer = extruder["buffer"].as<String>();
            String bufferStatus = extruder["buffer_status"].as<String>();
            #ifdef DEBUG_OUTPUT_FETCH
            DEBUG_PRINT("Tool Loaded: ");
            DEBUG_PRINTLN(toolLoaded ? "true" : "false");
            DEBUG_PRINT("Buffer: ");
            DEBUG_PRINTLN(buffer);
            DEBUG_PRINT("Buffer Status: ");
            DEBUG_PRINTLN(bufferStatus);
            #endif
        }
    } else {
        DEBUG_PRINTLN("System key not found in AFC.");
    }
    #ifdef DEBUG_OUTPUT_FETCH
    DEBUG_PRINT("Lane 1 Status: ");
    DEBUG_PRINTLN(legLoad[0]);
    DEBUG_PRINT("Lane 2 Status: ");
    DEBUG_PRINTLN(legLoad[1]);
    DEBUG_PRINT("Lane 3 Status: ");
    DEBUG_PRINTLN(legLoad[2]);
    DEBUG_PRINT("Lane 4 Status: ");
    DEBUG_PRINTLN(legLoad[3]);
    DEBUG_PRINT("Tool Status: ");
    DEBUG_PRINTLN(toolLoaded ? "true" : "false");
    DEBUG_PRINT("Current Load: ");
    DEBUG_PRINTLN(currentLoad);
    #endif
}