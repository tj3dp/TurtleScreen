#include <Preferences.h>
#include "wifi_manager.h"
#include "api_fetch.h"
#include "web_page.h"


void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Starting up... \n");

    preferences.begin("wifi-config", false);
    loadCredentials();

    if (!targetSSID.isEmpty() && !targetPassword.isEmpty()) {
        Serial.println("Connecting to saved Wi-Fi network");
        if (xTaskCreate(connectToWiFiTask, "WiFi Connect Task", 4096, NULL, 3, NULL) != pdPASS) {
            Serial.println("Failed to create WiFi Connect Task");
        }
        //xTaskCreate(lvgl_ui_task, "LVGL Init Task", 4096, NULL, 1, NULL);
    } else {
        setupWiFiAP();
       // xTaskCreate(lvgl_ui_task, "LVGL Init Task", 4096, NULL, 1, NULL);
    }


    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", webpage_html);
    });

    server.on("/setConfig", HTTP_POST, [](AsyncWebServerRequest *request) {
        if (request->hasParam("ssid", true) && request->hasParam("password", true) && request->hasParam("host", true)) {
            targetSSID = request->getParam("ssid", true)->value();
            targetPassword = request->getParam("password", true)->value();
            targetHost = request->getParam("host", true)->value();

            saveCredentials(targetSSID, targetPassword, targetHost);
            Serial.print("Host set as:");

            apiURL = "http://" + targetHost + "/printer/objects/query?AFC";
            Serial.println(apiURL);

            if (xTaskCreate(connectToWiFiTask, "WiFi Connect Task", 4096, NULL, 3, NULL) != pdPASS) {
                Serial.println("Failed to create WiFi Connect Task");
            }
            xTaskCreate(fetchDataTask, "Data Fetch Task", 4096, NULL, 2, NULL);

            request->send(200, "text/plain", "Configuration saved. Connecting to Wi-Fi...");
        } else {
            request->send(400, "text/plain", "Missing parameters.");
        }
    });

    server.begin(); 
}

void loop() {
    
}