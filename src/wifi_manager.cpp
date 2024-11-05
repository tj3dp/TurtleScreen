#include "wifi_manager.h"
#include <Preferences.h>
#include <Update.h>

const char* apSSID = "DeviceSetupAP";
const char* apPassword = "setup1234";
Preferences preferences;
AsyncWebServer server(80);

String targetSSID;
String targetPassword;
String targetHost;
TaskHandle_t WifITaskHandle = NULL;

void setupWiFiAP() {
    WiFi.softAP(apSSID, apPassword);
    Serial.println("Access Point started. Connect to 'DeviceSetupAP'.");
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());
}

void connectToWiFiTask(void *pvParameters) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(targetSSID.c_str(), targetPassword.c_str());

    int retryCount = 0;
    while (WiFi.status() != WL_CONNECTED && retryCount < 10) {
        Serial.print(".");
        retryCount++;
        delay(1000);
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected to Wi-Fi!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());

        // Now set the API URL with the target host
        apiURL = "http://" + targetHost + "/printer/objects/query?AFC";
        Serial.println("API URL: " + apiURL);  // For debugging

        // Start the data fetch task only after connecting to Wi-Fi
        if (xTaskCreate(fetchDataTask, "Data Fetch Task", 4096, NULL, 2, NULL) != pdPASS) {
            Serial.println("Failed to create Data Fetch Task");
        }
    } else {
        Serial.println("\nFailed to connect to Wi-Fi. Restarting AP mode.");
        setupWiFiAP();  // Fall back to AP mode if connection fails
    }

    vTaskDelete(NULL); // Delete the task after execution
}

void loadCredentials() {
    targetSSID = preferences.getString("ssid", "");
    targetPassword = preferences.getString("password", "");
    targetHost = preferences.getString("host", "");

    if (!targetSSID.isEmpty() && !targetPassword.isEmpty() && !targetHost.isEmpty()) {
        Serial.println("Loaded Wi-Fi credentials and target host from memory.");
        Serial.print("SSID: "); Serial.println(targetSSID);  // Print SSID
        Serial.print("Password: "); Serial.println(targetPassword);  // Print Password
        Serial.print("Host: "); Serial.println(targetHost);

        // Begin Wi-Fi connection
        WiFi.begin(targetSSID.c_str(), targetPassword.c_str());

        // Construct the API URL from the saved host
        apiURL = "http://" + targetHost + "/printer/objects/query?AFC";
        Serial.println("API URL: " + apiURL);  // Print API URL for debugging
    } else {
        Serial.println("No saved Wi-Fi credentials or host found.");
    }
}

void saveCredentials(const String& ssid, const String& password, const String& host) {
    preferences.putString("ssid", ssid);
    preferences.putString("password", password);
    preferences.putString("host", host);
    Serial.println("Wi-Fi credentials and host saved.");
}
