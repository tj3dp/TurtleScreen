#include <lvgl.h>
#include "ui.h"

#ifndef _UI_FUNCTIONS_H
#define _UI_FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

extern lv_color_t color;
extern int selected;
extern int legLane[12];
extern int legMapTool[12];

void afcBrushCall();
void afcCutCall();
void afcKickCall();
void afcParkCall();
void afcPoopCall();
void btPrepCall();

void g32Call();

void DoUnload();
void DoLoadTool(int tool);
void DoEjectLane(int lane);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif