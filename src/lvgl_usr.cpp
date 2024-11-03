#include <stdio.h> // sprintf
#include <Arduino.h>
#include "lvgl_hal.h"
#include "lvgl_usr.h"
#include "ui/ui.h"


void lv_popup_warning(const char * warning, bool clickable);
void lv_popup_remove(lv_event_t * e) ;

void lvgl_ui_task(void * parameter) {
    lvgl_hal_init();
    ui_init();
       for(;;) {
        lv_timer_handler();
        delay(5);
       }
}
