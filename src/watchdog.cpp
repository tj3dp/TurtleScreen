# include "watchdog.h"
volatile uint32_t apiTaskLastCheckIn = 0; 
const uint32_t WATCHDOG_TIMEOUT_MS = 60000; 

volatile bool apiTaskHeartbeat = false;
volatile bool lvglTaskHeartbeat = false;

void apiTaskCheckIn() {
    apiTaskLastCheckIn = xTaskGetTickCount();
}

void restartApiTask() {
    if (apiFetchTaskHandle != NULL) {
        vTaskDelete(apiFetchTaskHandle);
    }
    xTaskCreate(fetchDataTask, "API Fetch Task", 4096, NULL, 1, &apiFetchTaskHandle);
}

void restartLvglTask() {
    if (lvglUiTaskHandle != NULL) {
        vTaskDelete(lvglUiTaskHandle);
    }
    xTaskCreate(lvgl_ui_task, "LVGL UI Task", 4096, NULL, 1, &lvglUiTaskHandle);
}


void watchdog_task(void *param) {
    static uint32_t lastApiUpdate = 0;
    static uint32_t lastLvglUpdate = 0;

    while (1) {
        if (xTaskGetTickCount() - lastApiUpdate > pdMS_TO_TICKS(10000)) { 
            restartApiTask();
            lastApiUpdate = xTaskGetTickCount();
        }

        if (xTaskGetTickCount() - lastLvglUpdate > pdMS_TO_TICKS(10000)) { 
            restartLvglTask();
            lastLvglUpdate = xTaskGetTickCount();
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}