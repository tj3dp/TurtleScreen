#ifndef LVGL_HAL_H
#define LVGL_HAL_H

#ifdef T3DISPLAY
    #include <Arduino.h>
    #include "AXS15231B.h"
    #include <SPI.h>
    #include <CST816S.h>
    #include "pinout_t3.h"
    void tft_set_backlight(int8_t light);
#endif

#include "lvgl.h"
void lvgl_hal_init(void);

#endif