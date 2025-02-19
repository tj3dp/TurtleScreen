# include "watchdog.h"
volatile uint32_t apiTaskLastCheckIn = 0; 
const uint32_t WATCHDOG_TIMEOUT_MS = 60000; 

volatile bool apiTaskHeartbeat = false;
volatile bool lvglTaskHeartbeat = false;

void apiTaskCheckIn() 
{
    apiTaskLastCheckIn = xTaskGetTickCount();
}

void restartApiTask() 
{
    if (apiFetchTaskHandle != NULL) 
    {
        vTaskDelete(apiFetchTaskHandle);
    }
    xTaskCreate(fetchDataTask, "API Fetch Task", 4096, NULL, 8, &apiFetchTaskHandle);
}

void restartLvglTask() 
{
    if (lvglUiTaskHandle != NULL) 
    {
        vTaskDelete(lvglUiTaskHandle);
        lvglUiTaskHandle = NULL;
    }
    xTaskCreate(lvgl_ui_task, "LVGL UI Task", 4096, NULL, 10, &lvglUiTaskHandle);
}

void restartPostTask() 
{
    if (postTaskHandle != NULL) {
        vTaskDelete(postTaskHandle);
    }
    xTaskCreate(moonraker_post_task, "moonraker post", 4096, NULL, 6, &postTaskHandle);
}

void watchdog_task(void *param) 
{
    static uint32_t lastApiUpdate = 0;
    static uint32_t lastLvglUpdate = 0;

    while (1) 
    {
        if (xTaskGetTickCount() - lastApiUpdate > pdMS_TO_TICKS(10000)) 
        { 
            restartApiTask();
            lastApiUpdate = xTaskGetTickCount();
        }

        /*if (xTaskGetTickCount() - lastLvglUpdate > pdMS_TO_TICKS(5000)) { 
            restartLvglTask();
            lastLvglUpdate = xTaskGetTickCount();
        }*/
       if(!lvglTaskHeartbeat)
       {
            Serial.println("Bark: Restarting LVGL");
            restartLvglTask();
       }
       else
       {
            lvglTaskHeartbeat = false;
       }

        if (xTaskGetTickCount() - lastPostUpdate > pdMS_TO_TICKS(10000))
        { 
            restartPostTask();
            lastPostUpdate = xTaskGetTickCount();
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

