#ifndef LVGL_HAL_H
#define LVGL_HAL_H

#include <Arduino.h>
#include "AXS15231B.h"
#endif
#include <SPI.h>
#include <CST816S.h>

#include "pinout_t3.h"
#include "lvgl.h"

void lvgl_hal_init(void);
void tft_set_backlight(int8_t light);
