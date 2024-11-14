#include "ui_functions.h"
#include "moonraker.h"

lv_obj_t *gif_img;
lv_color_t color;

int colorChangeState = -1;

void tool0ChangeCall(lv_event_t * e){
    moonraker.post_gcode_to_queue("T0");
}
void tool1ChangeCall(lv_event_t * e){
    moonraker.post_gcode_to_queue("T1");
}
void tool2ChangeCall(lv_event_t * e){
    moonraker.post_gcode_to_queue("T2");
}
void tool3ChangeCall(lv_event_t * e){
    moonraker.post_gcode_to_queue("T3");
}

void setActiveColor(lv_event_t * e){
    color = lv_colorwheel_get_rgb(ui_Colorwheel1);
    if(activeColor.full != color.full) activeColor = color;
}

void setLoadedColor(lv_event_t * e){
    color = lv_colorwheel_get_rgb(ui_Colorwheel1);
    if(loadedColor.full != color.full) loadedColor = color;

}

void setUnloadedColor(lv_event_t * e){
    color = lv_colorwheel_get_rgb(ui_Colorwheel1);
    if(unloadedColor.full != color.full) unloadedColor = color;
}

void setButtonColor(lv_event_t * e) {

    color = lv_colorwheel_get_rgb(ui_Colorwheel1);
    if(buttonColor.full != color.full) buttonColor = color;
    if(_ui_theme_color_Blue[1] != lv_color_to_hex(color)) _ui_theme_color_Blue[1] =lv_color_to_hex(color);
    ui_theme_set(1);
}

void saveColorWheel(lv_event_t * e){
    color = lv_colorwheel_get_rgb(ui_Colorwheel1);
}
