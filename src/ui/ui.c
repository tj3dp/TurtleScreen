// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: BoxTurtle

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void GifPop_Animation(lv_obj_t * TargetObject, int delay);


// SCREEN: ui_LaneSelect
void ui_LaneSelect_screen_init(void);
lv_obj_t * ui_LaneSelect;
lv_obj_t * ui_TitlePanel;
lv_obj_t * ui_TitleText;
lv_obj_t * ui_ToolButtonContainer;
void ui_event_Tool0Button(lv_event_t * e);
lv_obj_t * ui_Tool0Button;
void ui_event_Tool1Button(lv_event_t * e);
lv_obj_t * ui_Tool1Button;
void ui_event_Tool2Button(lv_event_t * e);
lv_obj_t * ui_Tool2Button;
void ui_event_Tool3Button(lv_event_t * e);
lv_obj_t * ui_Tool3Button;
void ui_event_Tool4Button(lv_event_t * e);
lv_obj_t * ui_Tool4Button;
void ui_event_Tool5Button(lv_event_t * e);
lv_obj_t * ui_Tool5Button;
void ui_event_Tool6Button(lv_event_t * e);
lv_obj_t * ui_Tool6Button;
void ui_event_Tool7Button(lv_event_t * e);
lv_obj_t * ui_Tool7Button;
void ui_event_Tool8Button(lv_event_t * e);
lv_obj_t * ui_Tool8Button;
void ui_event_Tool9Button(lv_event_t * e);
lv_obj_t * ui_Tool9Button;
void ui_event_Tool10Button(lv_event_t * e);
lv_obj_t * ui_Tool10Button;
void ui_event_Tool11Button(lv_event_t * e);
lv_obj_t * ui_Tool11Button;
void ui_event_SettingsButton(lv_event_t * e);
lv_obj_t * ui_SettingsButton;
void ui_event_ControlButton(lv_event_t * e);
lv_obj_t * ui_ControlButton;
lv_obj_t * ui_Panel4;
lv_obj_t * ui_Image1;
lv_obj_t * ui_CurrentNozzleTemp;
lv_obj_t * ui_Image2;
lv_obj_t * ui_CurrentBedTemp;
lv_obj_t * ui_Printstatus;
lv_obj_t * ui_PrintProgressBar;
lv_obj_t * ui_PercentComplete;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Label3;
lv_obj_t * ui_SwitchStatusPanel;
lv_obj_t * ui_Label14;
lv_obj_t * ui_HubStatus;
lv_obj_t * ui_ToolStatus;
lv_obj_t * ui_Label17;
lv_obj_t * ui_GifPanel;
lv_obj_t * ui_NextTools;
lv_obj_t * ui_PreviousTools;
// CUSTOM VARIABLES
lv_obj_t * uic_Tool0Button;
lv_obj_t * uic_Tool1Button;
lv_obj_t * uic_Tool2Button;
lv_obj_t * uic_Tool3Button;
lv_obj_t * uic_Tool4Button;
lv_obj_t * uic_Tool5Button;
lv_obj_t * uic_Tool6Button;
lv_obj_t * uic_Tool7Button;
lv_obj_t * uic_Tool8Button;
lv_obj_t * uic_Tool9Button;
lv_obj_t * uic_Tool10Button;
lv_obj_t * uic_Tool11Button;
lv_obj_t * uic_CurrentNozzleTemp;


// SCREEN: ui_CurrentLaneToggle
void ui_CurrentLaneToggle_screen_init(void);
lv_obj_t * ui_CurrentLaneToggle;
lv_obj_t * ui_Panel3;
lv_obj_t * ui_ActivateLane;
lv_obj_t * ui_ActivateLaneLabel;
lv_obj_t * ui_EjectLane;
lv_obj_t * ui_EjectLaneLabel;
void ui_event_BackLaneToggle(lv_event_t * e);
lv_obj_t * ui_BackLaneToggle;
lv_obj_t * ui_Image6;
lv_obj_t * ui_Label23;
// CUSTOM VARIABLES


// SCREEN: ui_GeneralControl
void ui_GeneralControl_screen_init(void);
lv_obj_t * ui_GeneralControl;
lv_obj_t * ui_Panel5;
lv_obj_t * ui_AFCBrush;
lv_obj_t * ui_Label7;
lv_obj_t * ui_AFCCut;
lv_obj_t * ui_Label8;
lv_obj_t * ui_AFCKick;
lv_obj_t * ui_Label9;
lv_obj_t * ui_AFCPark;
lv_obj_t * ui_Label10;
lv_obj_t * ui_AFCPoop;
lv_obj_t * ui_Label11;
lv_obj_t * ui_BTPrep;
lv_obj_t * ui_Label12;
lv_obj_t * ui_BTToolUnload;
lv_obj_t * ui_Label13;
void ui_event_Button11(lv_event_t * e);
lv_obj_t * ui_Button11;
lv_obj_t * ui_Image7;
lv_obj_t * ui_Label24;
// CUSTOM VARIABLES


// SCREEN: ui_ColorSettings
void ui_ColorSettings_screen_init(void);
lv_obj_t * ui_ColorSettings;
lv_obj_t * ui_Panel6;
lv_obj_t * ui_Label1;
void ui_event_SetActiveColor(lv_event_t * e);
lv_obj_t * ui_SetActiveColor;
lv_obj_t * ui_Label5;
void ui_event_SetLoadedColor(lv_event_t * e);
lv_obj_t * ui_SetLoadedColor;
lv_obj_t * ui_Label6;
void ui_event_SetButtonColor(lv_event_t * e);
lv_obj_t * ui_SetButtonColor;
lv_obj_t * ui_Label18;
void ui_event_SetUnloadedColor(lv_event_t * e);
lv_obj_t * ui_SetUnloadedColor;
lv_obj_t * ui_Label19;
void ui_event_BackColorSettings(lv_event_t * e);
lv_obj_t * ui_BackColorSettings;
lv_obj_t * ui_Image8;
lv_obj_t * ui_Label25;
// CUSTOM VARIABLES


// SCREEN: ui_ColorSelect
void ui_ColorSelect_screen_init(void);
lv_obj_t * ui_ColorSelect;
lv_obj_t * ui_Colorwheel1;
void ui_event_ReturnColorSelect(lv_event_t * e);
lv_obj_t * ui_ReturnColorSelect;
lv_obj_t * ui_Image3;
lv_obj_t * ui_Label20;
void ui_event_SaveColorSelect(lv_event_t * e);
lv_obj_t * ui_SaveColorSelect;
lv_obj_t * ui_Image4;
lv_obj_t * ui_Label21;
// CUSTOM VARIABLES

// EVENTS
lv_obj_t * ui____initial_actions0;

// IMAGES AND IMAGE SETS
const lv_img_dsc_t * ui_imgset_255621937[1] = {&ui_img_922480046};
const lv_img_dsc_t * ui_imgset_639896326[12] = {&ui_img_642937331, &ui_img_642936306, &ui_img_539412392, &ui_img_542316787, &ui_img_642943729, &ui_img_642942704, &ui_img_642941679, &ui_img_642940654, &ui_img_642948077, &ui_img_642947052, &ui_img_642946043, &ui_img_642945018};
const lv_img_dsc_t * ui_imgset_print_bar[2] = {&ui_img_print_bar1_png, &ui_img_print_bar2_png};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////
void GifPop_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 1000);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
    lv_anim_set_values(&PropertyAnimation_0, -100, 10);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_overshoot);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 1000);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);
    ui_anim_user_data_t * PropertyAnimation_1_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_1_user_data->target = TargetObject;
    PropertyAnimation_1_user_data->val = -1;
    lv_anim_t PropertyAnimation_1;
    lv_anim_init(&PropertyAnimation_1);
    lv_anim_set_time(&PropertyAnimation_1, 1000);
    lv_anim_set_user_data(&PropertyAnimation_1, PropertyAnimation_1_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_1, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_1, 58, -10);
    lv_anim_set_path_cb(&PropertyAnimation_1, lv_anim_path_ease_in);
    lv_anim_set_delay(&PropertyAnimation_1, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_1, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_1, 1000);
    lv_anim_set_playback_delay(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_1, 0);
    lv_anim_set_early_apply(&PropertyAnimation_1, false);
    lv_anim_start(&PropertyAnimation_1);

}

///////////////////// FUNCTIONS ////////////////////
void ui_event_Tool0Button(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        selectedTool = 0;
        _ui_screen_change(&ui_CurrentLaneToggle, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_CurrentLaneToggle_screen_init);
    }
}

void ui_event_Tool1Button(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        selectedTool = 1;
        _ui_screen_change(&ui_CurrentLaneToggle, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_CurrentLaneToggle_screen_init);
    }
}

void ui_event_Tool2Button(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        selectedTool = 2;
        _ui_screen_change(&ui_CurrentLaneToggle, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_CurrentLaneToggle_screen_init);
    }
}

void ui_event_Tool3Button(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        selectedTool = 3;
        _ui_screen_change(&ui_CurrentLaneToggle, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_CurrentLaneToggle_screen_init);
    }
}

void ui_event_Tool4Button(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        selectedTool = 4;
        _ui_screen_change(&ui_CurrentLaneToggle, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_CurrentLaneToggle_screen_init);
    }
}

void ui_event_Tool5Button(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        selectedTool = 5;
        _ui_screen_change(&ui_CurrentLaneToggle, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_CurrentLaneToggle_screen_init);
    }
}

void ui_event_Tool6Button(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        selectedTool = 6;
        _ui_screen_change(&ui_CurrentLaneToggle, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_CurrentLaneToggle_screen_init);
    }
}

void ui_event_Tool7Button(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        selectedTool = 7;
        _ui_screen_change(&ui_CurrentLaneToggle, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_CurrentLaneToggle_screen_init);
    }
}

void ui_event_Tool8Button(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        selectedTool = 8;
        _ui_screen_change(&ui_CurrentLaneToggle, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_CurrentLaneToggle_screen_init);
    }
}

void ui_event_Tool9Button(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        selectedTool = 9;
        _ui_screen_change(&ui_CurrentLaneToggle, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_CurrentLaneToggle_screen_init);
    }
}

void ui_event_Tool10Button(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        selectedTool = 10;
        _ui_screen_change(&ui_CurrentLaneToggle, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_CurrentLaneToggle_screen_init);
    }
}

void ui_event_Tool11Button(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        selectedTool = 11;
        _ui_screen_change(&ui_CurrentLaneToggle, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_CurrentLaneToggle_screen_init);
    }
}

void ui_event_SettingsButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ColorSettings, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_ColorSettings_screen_init);
    }
}

void ui_event_ControlButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_GeneralControl, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_GeneralControl_screen_init);
    }
}

void ui_event_BackLaneToggle(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_LaneSelect, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_LaneSelect_screen_init);
    }
}

void ui_event_Button11(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_LaneSelect, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_LaneSelect_screen_init);
    }
}

void ui_event_SetActiveColor(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ColorSelect, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_ColorSelect_screen_init);
    colorChangeState = 1;
    }
}

void ui_event_SetLoadedColor(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ColorSelect, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_ColorSelect_screen_init);
    colorChangeState =2;
    }
}

void ui_event_SetButtonColor(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ColorSelect, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_ColorSelect_screen_init);
    colorChangeState = 4;
    }
}

void ui_event_SetUnloadedColor(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ColorSelect, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_ColorSelect_screen_init);
    colorChangeState =3;
    }
}

void ui_event_BackColorSettings(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_LaneSelect, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_LaneSelect_screen_init);
    }
}

void ui_event_ReturnColorSelect(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_ColorSettings, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_ColorSettings_screen_init);
        colorChangeState = -1;
    }
}

void ui_event_SaveColorSelect(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_LaneSelect, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_LaneSelect_screen_init);
        saveColorWheel(e);
        switch (colorChangeState){
            case 1:
                    setActiveColor(e);
                    colorChangeState = -1;
                break;
            case 2:
                    setLoadedColor(e);
                    colorChangeState = -1;
                break;
            case 3:
                    setUnloadedColor(e);
                    colorChangeState = -1;
                break;
            case 4:
                    setButtonColor(e);
                    colorChangeState = -1;
                break;
            case -1:
                break;
        }
        colorChangeState = -1;
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_LaneSelect_screen_init();
    ui_CurrentLaneToggle_screen_init();
    ui_GeneralControl_screen_init();
    ui_ColorSettings_screen_init();
    ui_ColorSelect_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_LaneSelect);
}
