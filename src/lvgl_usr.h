#ifndef LVGL_USR_H
#define LVGL_USR_H
#include <stdio.h> // sprintf
#include <Arduino.h>
#include "lvgl_hal.h"
#include "lvgl_usr.h"
#include "ui/ui.h"
#include "api_fetch.h"
#include "moonraker.h"

void lvgl_ui_task(void * parameter);
extern TaskHandle_t lvglUiTaskHandle;
extern uint32_t lastLvglUpdate;
extern int activeLane;

#endif
