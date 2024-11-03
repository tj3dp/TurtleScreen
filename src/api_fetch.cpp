#include "api_fetch.h"

String apiURL;
float eventTime;           
bool leg1Load;              
bool leg2Load;              
bool leg3Load;              
bool leg4Load;            
const char* currentLoad;  
bool toolLoaded; 
bool loadedToHub;

void fetchDataTask(void *pvParameters) {
    while (true) {
        if (WiFi.status() == WL_CONNECTED && !apiURL.isEmpty()) {
            Serial.print("Trying to grab API data \n");
            HTTPClient http;
            http.begin(apiURL);
            int httpResponseCode = http.GET();

            if (httpResponseCode == 200) {
                String payload = http.getString();
                Serial.println("Received data:");
                #ifdef DEBUGOUTPUT
                Serial.println(payload);
                #endif
                // Parse JSON data
                ParseAPIResponse(payload);
            } else {
                Serial.print("HTTP error: ");
                Serial.println(httpResponseCode);
            }
            http.end();
        } else {
            Serial.println("Wi-Fi not connected or API URL not set");
        }
        delay(30000);  // Fetch data every 30 seconds
    }
}

void ParseAPIResponse(const String& jsonResponse) {
    Serial.println("Running API Parse");
    DynamicJsonDocument doc(1024); 
    DeserializationError error = deserializeJson(doc, jsonResponse);

    if (error) {
        Serial.print("Failed to parse JSON: ");
        Serial.println(error.f_str());
        return;
    }

    JsonObject result = doc["result"];
    eventTime = result["eventtime"];
    JsonObject status = result["status"];
    JsonObject afc = status["AFC"];

#ifdef DEBUGOUTPUT
    Serial.print("Turtle_1 Object: ");
    Serial.println(afc["Turtle_1"].as<String>());
#endif
    for (int leg = 1; leg <= 4; ++leg) {
        String legKey = "leg" + String(leg);
        if (afc.containsKey("Turtle_1") && afc["Turtle_1"].containsKey(legKey.c_str())) {
            JsonObject legData = afc["Turtle_1"][legKey];
            bool load = legData["load"];
            bool prep = legData["prep"];
            loadedToHub = legData["loaded_to_hub"];
            int lane = legData["LANE"];
#ifdef DEBUGOUTPUT
            Serial.print("Lane ");
            Serial.print(lane);
            Serial.print(" - Load: ");
            Serial.print(load ? "true" : "false");
            Serial.print(", Prep: ");
            Serial.print(prep ? "true" : "false");
            Serial.print(", Loaded to Hub: ");
            Serial.println(loadedToHub ? "true" : "false");
#endif
            if (lane == 1) {
                leg1Load = load; 
            }
            else if (lane == 2) {
                leg2Load = load;
            }
            else if (lane == 3) {
                leg3Load = load;
            }
            else if (lane == 4) {
                leg4Load = load;
            }
        } else {
            Serial.print("Checking key: ");
            Serial.println(legKey);
            Serial.println("Key not found.");
        }
    }

    if (status.containsKey("AFC")) {
        JsonObject afcStatus = status["AFC"];
        
        if (afcStatus.containsKey("system")) {
            JsonObject system = afcStatus["system"];

#ifdef DEBUGOUTPUT
            Serial.print("System Object: ");
            serializeJson(system, Serial);
            Serial.println(); 
#endif
            currentLoad = system["current_load"].as<const char*>();
            toolLoaded = system["tool_loaded"];
            loadedToHub = system["hub_loaded"];  

#ifdef DEBUGOUTPUT
            Serial.print("Raw tool_loaded value: ");
            Serial.println(toolLoaded ? "true" : "false"); 
#endif
            JsonVariant buffer = system["buffer"];
#ifdef DEBUGOUTPUT
            Serial.print("Buffer: ");
            if (buffer.isNull()) {
                Serial.println("null");
            } else {
                Serial.println(buffer.as<String>());
            }
#endif
        } else {
            Serial.println("System key not found in AFC.");
        }
    } else {
        Serial.println("AFC key not found in status.");
    }

    Serial.print("Lane 1 Status: "); Serial.println(leg1Load);
    Serial.print("Lane 2 Status: "); Serial.println(leg2Load);
    Serial.print("Lane 3 Status: "); Serial.println(leg3Load);
    Serial.print("Lane 4 Status: "); Serial.println(leg4Load);
    Serial.print("Tool Status: "); Serial.println(toolLoaded ? "true" : "false");
    Serial.print("Hub Status: "); Serial.println(loadedToHub ? "true" : "false");
    Serial.print("Current Load: "); Serial.println(currentLoad);
}

