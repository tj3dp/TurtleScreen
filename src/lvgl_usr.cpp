#include "lvgl_usr.h"

void lv_popup_warning(const char * warning, bool clickable);
void lv_popup_remove(lv_event_t * e) ;
uint32_t lastLvglUpdate;


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

void lvgl_set_current_leg() {
    if (currentLoadChanged == false) return;
    if (currentLoadBuffer != nullptr) {
        if (strlen(currentLoadBuffer) > 0) {
            const char *labelText = lv_label_get_text(uic_CurrentLeg);
            if (strcmp(labelText, currentLoadBuffer) != 0) {
                lv_label_set_text(uic_CurrentLeg, currentLoadBuffer);
            }
        }
        currentLoadChanged = false;
    } 
    else {
        const char *currentText = lv_label_get_text(uic_CurrentLeg);
        if (strcmp(currentText, "None") != 0) {
            lv_label_set_text(uic_CurrentLeg, "None");
        }
        currentLoadChanged = false;
    }
}

void lvgl_set_tool_status(){
    const char *toolStatus = lv_label_get_text(uic_ToolStatus);
    if (strcmp(toolStatus, currentLoadBuffer) != 0){
        lv_label_set_text(uic_ToolStatus, booleanHelper(toolLoaded));
    }
}

void lvgl_set_hub_status(){
    const char *hubStatus = lv_label_get_text(ui_HubStatus);
    if (strcmp(hubStatus, currentLoadBuffer) != 0){
        lv_label_set_text(ui_HubStatus, booleanHelper(loadedToHub));
    }
}

void lvgl_set_leg_status(){
    const char *leg1Status = lv_label_get_text(ui_Leg1Status);
    if (strcmp(leg1Status, currentLoadBuffer) != 0){
        lv_label_set_text(ui_Leg1Status, booleanHelper(leg1Load));
    }
    const char *leg2Status = lv_label_get_text(ui_Leg2Status);
    if (strcmp(leg2Status, currentLoadBuffer) != 0){
        lv_label_set_text(ui_Leg2Status, booleanHelper(leg2Load));
    }
    const char *leg3Status = lv_label_get_text(ui_Leg3Status);
    if (strcmp(leg3Status, currentLoadBuffer) != 0){
        lv_label_set_text(ui_Leg3Status, booleanHelper(leg3Load));
    }
    const char *leg4Status = lv_label_get_text(ui_Leg4Status);
    if (strcmp(leg4Status, currentLoadBuffer) != 0){
        lv_label_set_text(ui_Leg4Status, booleanHelper(leg4Load));
    }
}

void lvgl_set_current_color(){
    
}

void lvgl_set_params(){
        lvgl_set_current_leg();
        lvgl_set_tool_status();
        lvgl_set_hub_status();
        lvgl_set_leg_status();
        
}

void lvgl_ui_task(void * parameter) {
    lvgl_hal_init();
    ui_init();
       for(;;) {
        lvgl_set_params();
        lv_timer_handler();
        lastLvglUpdate = xTaskGetTickCount();
        vTaskDelay(pdMS_TO_TICKS(5));
       }
}

