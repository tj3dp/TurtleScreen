#include "lvgl_usr.h"
#include "api_fetch.h"

void lv_popup_warning(const char * warning, bool clickable);
void lv_popup_remove(lv_event_t * e) ;
uint32_t lastLvglUpdate;
lv_color_t activeColor =    lv_color_hex(0x0000ff);
lv_color_t loadedColor =    lv_color_hex(0x00ff00);
lv_color_t unloadedColor =  lv_color_hex(0xff0000);
lv_color_t buttonColor =    lv_color_hex(0x202020);

int activeLane = -1;

const char* booleanHelper(bool value){
    const char* temp;
    switch(value){
        case true:
                temp = "True";
            break;
        case false:
                temp = "False";
            break;
    }
    return temp;
}

uint32_t lv_color_to_hex(lv_color_t color) {
    uint8_t red = color.ch.red;
    uint8_t green = (color.ch.green_h << 3) | color.ch.green_l;
    uint8_t blue = color.ch.blue;

    uint32_t hexValue = (red << 16) | (green << 8) | blue;

    return hexValue;
}

void lvgl_set_current_leg() 
{
   if (strlen(currentLoadBuffer) == 5) 
        activeLane = atoi(&currentLoadBuffer[4]);
   else 
        activeLane = -1;
}

void lvgl_set_tool_status()
{
    const char *toolStatus = lv_label_get_text(ui_LblToolStatus);
    if (strcmp(toolStatus, extruderLaneLoaded.c_str()) != -1)
    {
        lv_label_set_text(ui_LblToolStatus, extruderLaneLoaded.c_str());
    }
}

void lvgl_set_hub_status()
{
    const char *hubStatus = lv_label_get_text(ui_LblHubStatus);
    if (strcmp(hubStatus, booleanHelper(loadedToHub)) != 0)
    {
        lv_label_set_text(ui_LblHubStatus, booleanHelper(loadedToHub));
    }
}

void lvgl_set_leg_status()
{
    lv_obj_t* slots[4] = {ui_LblSlot0, ui_LblSlot1, ui_LblSlot2, ui_LblSlot3}; 
    lv_obj_t* btn[4]   = {ui_BtnSlot0, ui_BtnSlot1, ui_BtnSlot2, ui_BtnSlot3}; 

    for (int n = 0; n <= 3; ++n)
    {
        char buffer[20];
        sprintf(buffer, "Lane%d\nT%d", legLane[n], legMapTool[n]);
        if(String(lv_label_get_text(slots[n])) != String(buffer) )
            lv_label_set_text(slots[n], buffer);

        //lv_obj_set_style_bg_color(btn[n], activeLane==legLane[n] ? activeColor : legLoad[n] ? loadedColor : unloadedColor, LV_PART_MAIN);
        lv_obj_set_style_bg_color(btn[n], lv_color_hex(legColor[n]), LV_PART_MAIN);
        }
}

void lvgl_set_nozzle_temp()
{
    if(moonraker.data.nozzle_actual != atoi(lv_label_get_text(ui_LblNozzle))){
        char buffer[12];
        sprintf(buffer, "%d", moonraker.data.nozzle_actual);
        lv_label_set_text(ui_LblNozzle, buffer);
    }
}

void lvgl_set_bed_temp(){
    if(moonraker.data.nozzle_actual != atoi(lv_label_get_text(ui_LblBed))){
        char buffer[12];
        sprintf(buffer, "%d", moonraker.data.bed_actual);
        lv_label_set_text(ui_LblBed, buffer);
    }
}

void lvgl_set_params(){
        lvgl_set_current_leg();
        lvgl_set_tool_status();
        lvgl_set_hub_status();
        lvgl_set_leg_status();
        lvgl_set_nozzle_temp();
        lvgl_set_bed_temp();
}

void lvgl_ui_task(void * parameter) {
    lvgl_hal_init();
    ui_init();
    for(;;) {
        lvgl_set_params();
        lv_timer_handler();
        lastLvglUpdate = xTaskGetTickCount();
        lvglTaskHeartbeat = true;
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

