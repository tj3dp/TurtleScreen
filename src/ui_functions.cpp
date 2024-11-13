#include "ui_functions.h"
#include "moonraker.h"

lv_obj_t *gif_img;


void tool0Pressed(lv_event_t * e){
    moonraker.post_gcode_to_queue("T0");
}
void tool1Pressed(lv_event_t * e){
    moonraker.post_gcode_to_queue("T1");
}
void tool2Pressed(lv_event_t * e){
    moonraker.post_gcode_to_queue("T2");
}
void tool3Pressed(lv_event_t * e){
    moonraker.post_gcode_to_queue("T3");
}
