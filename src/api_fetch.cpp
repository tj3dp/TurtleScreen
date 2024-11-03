#include "api_fetch.h"

String apiURL;

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
                Serial.println(payload);

                // Parse JSON data
                parseApiResponse(payload);
            } else {
                Serial.print("HTTP error: ");
                Serial.println(httpResponseCode);
            }
            http.end();
        } else {
            Serial.println("Wi-Fi not connected or API URL not set");
        }
        delay(60000);  // Fetch data every 60 seconds
    }
}

void parseApiResponse(const String& json) {
    StaticJsonDocument<2048> doc;
    DeserializationError error = deserializeJson(doc, json);
    if (error) {
        Serial.print("JSON parsing failed: ");
        Serial.println(error.f_str());
        return;
    }

    // Extract values from JSON
    float eventTime = doc["result"]["eventtime"];
    bool toolLoaded = doc["result"]["status"]["system"]["tool_loaded"];
    const char* currentLoad = doc["result"]["status"]["system"]["current_load"];
    bool leg1Load = doc["result"]["status"]["AFC"]["Turtle_1"]["leg1"]["load"];

    Serial.println("Event Time: " + String(eventTime));
    Serial.println("Tool Loaded: " + String(toolLoaded));
    Serial.println("Current Load: " + String(currentLoad));
    Serial.println("Leg1 Load: " + String(leg1Load));
}

