# include "watchdog.h"
volatile uint32_t apiTaskLastCheckIn = 0; // Stores the last time apiTask checked in
const uint32_t WATCHDOG_TIMEOUT_MS = 60000; // 1-minute timeout for the example

volatile bool apiTaskHeartbeat = false;
volatile bool lvglTaskHeartbeat = false;

// Function for the API fetch task to "check in" periodically
void apiTaskCheckIn() {
    apiTaskLastCheckIn = xTaskGetTickCount();
}

void restartApiTask() {
    if (apiFetchTaskHandle != NULL) {
        vTaskDelete(apiFetchTaskHandle); // Terminate the existing task
    }
    // Create a new API fetch task
    xTaskCreate(fetchDataTask, "API Fetch Task", 4096, NULL, 1, &apiFetchTaskHandle);
}

void restartLvglTask() {
    if (lvglUiTaskHandle != NULL) {
        vTaskDelete(lvglUiTaskHandle); // Terminate the existing task
    }
    // Create a new LVGL UI task
    xTaskCreate(lvgl_ui_task, "LVGL UI Task", 4096, NULL, 1, &lvglUiTaskHandle);
}


// The watchdog task itself
void watchdog_task(void *param) {
    static uint32_t lastApiUpdate = 0;
    static uint32_t lastLvglUpdate = 0;

    while (1) {
        // Monitor the API Fetch task
        if (xTaskGetTickCount() - lastApiUpdate > pdMS_TO_TICKS(10000)) { // 10-second timeout
            restartApiTask();
            lastApiUpdate = xTaskGetTickCount(); // Reset the timer after restart
        }

        // Monitor the LVGL UI task
        if (xTaskGetTickCount() - lastLvglUpdate > pdMS_TO_TICKS(10000)) { // 10-second timeout
            restartLvglTask();
            lastLvglUpdate = xTaskGetTickCount(); // Reset the timer after restart
        }

        vTaskDelay(pdMS_TO_TICKS(1000)); // Check every second
    }
}