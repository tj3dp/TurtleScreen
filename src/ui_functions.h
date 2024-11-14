#include <lvgl.h>
#include "ui/ui.h"

#ifndef _UI_FUNCTIONS_H
#define _UI_FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

extern lv_color_t color;
extern int colorChangeState;

void tool0ChangeCall(lv_event_t * e);
void tool1ChangeCall(lv_event_t * e);
void tool2ChangeCall(lv_event_t * e);
void tool3ChangeCall(lv_event_t * e);
void setActiveColor(lv_event_t * e);
void setLoadedColor(lv_event_t * e);
void setUnloadedColor(lv_event_t * e);
void setButtonColor(lv_event_t * e);
void saveColorWheel(lv_event_t * e);
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif