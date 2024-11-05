#ifndef LVGL_USR_H
#define LVGL_USR_H
#include "api_fetch.h"

void lvgl_ui_task(void * parameter);
extern TaskHandle_t lvglUiTaskHandle;
extern uint32_t lastLvglUpdate;
#endif
