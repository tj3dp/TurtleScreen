#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "api_fetch.h"
#include "esp_mac.h"
#include "lvgl_usr.h"
#include "projdefs.h"
#include "lvgl_hal.h"
#include "moonraker.h"


void watchdog_task(void *parameters);
#ifndef pdMS_TO_TICKS
#define pdMS_TO_TICKS(x) ((x) / portTICK_PERIOD_MS)
#endif
