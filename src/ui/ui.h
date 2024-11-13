// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: BoxTurtle

#ifndef _BOXTURTLE_UI_H
#define _BOXTURTLE_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lib/lvgl/lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"

void GifPop_Animation(lv_obj_t * TargetObject, int delay);

// SCREEN: ui_LaneSelect
void ui_LaneSelect_screen_init(void);
extern lv_obj_t * ui_LaneSelect;
extern lv_obj_t * ui_TitlePanel;
extern lv_obj_t * ui_TitleText;
extern lv_obj_t * ui_ToolButtonContainer;
void ui_event_Tool0Button(lv_event_t * e);
extern lv_obj_t * ui_Tool0Button;
void ui_event_Tool1Button(lv_event_t * e);
extern lv_obj_t * ui_Tool1Button;
void ui_event_Tool2Button(lv_event_t * e);
extern lv_obj_t * ui_Tool2Button;
void ui_event_Tool3Button(lv_event_t * e);
extern lv_obj_t * ui_Tool3Button;
void ui_event_Button6(lv_event_t * e);
extern lv_obj_t * ui_Button6;
extern lv_obj_t * ui_Panel4;
extern lv_obj_t * ui_Image1;
extern lv_obj_t * ui_CurrentNozzleTemp;
extern lv_obj_t * ui_Image2;
extern lv_obj_t * ui_CurrentBedTemp;
extern lv_obj_t * ui_Printstatus;
extern lv_obj_t * ui_PrintProgressBar;
extern lv_obj_t * ui_PercentComplete;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_SwitchStatusPanel;
extern lv_obj_t * ui_Label14;
extern lv_obj_t * ui_HubStatus;
extern lv_obj_t * ui_ToolStatus;
extern lv_obj_t * ui_Label17;
extern lv_obj_t * ui_GifPanel;
void ui_event_Button9(lv_event_t * e);
extern lv_obj_t * ui_Button9;
// CUSTOM VARIABLES
extern lv_obj_t * uic_Tool0Button;
extern lv_obj_t * uic_Tool1Button;
extern lv_obj_t * uic_Tool2Button;
extern lv_obj_t * uic_Tool3Button;
extern lv_obj_t * uic_CurrentNozzleTemp;

// SCREEN: ui_CurrentLaneToggle
void ui_CurrentLaneToggle_screen_init(void);
extern lv_obj_t * ui_CurrentLaneToggle;
extern lv_obj_t * ui_Panel3;
extern lv_obj_t * ui_ActivateLane;
extern lv_obj_t * ui_ActivateLaneLabel;
extern lv_obj_t * ui_EjectLane;
extern lv_obj_t * ui_EjectLaneLabel;
void ui_event_Button10(lv_event_t * e);
extern lv_obj_t * ui_Button10;
extern lv_obj_t * ui_Image6;
extern lv_obj_t * ui_Label23;
// CUSTOM VARIABLES

// SCREEN: ui_GeneralControl
void ui_GeneralControl_screen_init(void);
extern lv_obj_t * ui_GeneralControl;
extern lv_obj_t * ui_Panel5;
extern lv_obj_t * ui_AFCBrush;
extern lv_obj_t * ui_Label7;
extern lv_obj_t * ui_AFCCut;
extern lv_obj_t * ui_Label8;
extern lv_obj_t * ui_AFCKick;
extern lv_obj_t * ui_Label9;
extern lv_obj_t * ui_AFCPark;
extern lv_obj_t * ui_Label10;
extern lv_obj_t * ui_AFCPoop;
extern lv_obj_t * ui_Label11;
extern lv_obj_t * ui_BTPrep;
extern lv_obj_t * ui_Label12;
extern lv_obj_t * ui_BTToolUnload;
extern lv_obj_t * ui_Label13;
void ui_event_Button11(lv_event_t * e);
extern lv_obj_t * ui_Button11;
extern lv_obj_t * ui_Image7;
extern lv_obj_t * ui_Label24;
// CUSTOM VARIABLES

// SCREEN: ui_ColorSettings
void ui_ColorSettings_screen_init(void);
extern lv_obj_t * ui_ColorSettings;
extern lv_obj_t * ui_Panel6;
extern lv_obj_t * ui_Label1;
void ui_event_Button2(lv_event_t * e);
extern lv_obj_t * ui_Button2;
extern lv_obj_t * ui_Label5;
void ui_event_Button3(lv_event_t * e);
extern lv_obj_t * ui_Button3;
extern lv_obj_t * ui_Label6;
void ui_event_Button4(lv_event_t * e);
extern lv_obj_t * ui_Button4;
extern lv_obj_t * ui_Label18;
void ui_event_Button5(lv_event_t * e);
extern lv_obj_t * ui_Button5;
extern lv_obj_t * ui_Label19;
void ui_event_Button12(lv_event_t * e);
extern lv_obj_t * ui_Button12;
extern lv_obj_t * ui_Image8;
extern lv_obj_t * ui_Label25;
// CUSTOM VARIABLES

// SCREEN: ui_ColorSelect
void ui_ColorSelect_screen_init(void);
extern lv_obj_t * ui_ColorSelect;
extern lv_obj_t * ui_Colorwheel1;
void ui_event_Button7(lv_event_t * e);
extern lv_obj_t * ui_Button7;
extern lv_obj_t * ui_Image3;
extern lv_obj_t * ui_Label20;
void ui_event_Button8(lv_event_t * e);
extern lv_obj_t * ui_Button8;
extern lv_obj_t * ui_Image4;
extern lv_obj_t * ui_Label21;
// CUSTOM VARIABLES

// EVENTS

extern lv_obj_t * ui____initial_actions0;

// IMAGES AND IMAGE SETS
LV_IMG_DECLARE(ui_img_642937331);    // assets/extruder-0.png
LV_IMG_DECLARE(ui_img_642936306);    // assets/extruder-1.png
LV_IMG_DECLARE(ui_img_642943729);    // assets/extruder-2.png
LV_IMG_DECLARE(ui_img_642942704);    // assets/extruder-3.png
LV_IMG_DECLARE(ui_img_settings_png);    // assets/settings.png
LV_IMG_DECLARE(ui_img_filament_png);    // assets/filament.png
LV_IMG_DECLARE(ui_img_bed_png);    // assets/bed.png
LV_IMG_DECLARE(ui_img_986727804);    // assets/fine-tune.png
LV_IMG_DECLARE(ui_img_1470730272);    // assets/arrow-left.png
LV_IMG_DECLARE(ui_img_complete_png);    // assets/complete.png
LV_IMG_DECLARE(ui_img_922480046);    // assets/2602507-200.png
LV_IMG_DECLARE(ui_img_539412392);    // assets/extruder-10.png
LV_IMG_DECLARE(ui_img_542316787);    // assets/extruder-11.png
LV_IMG_DECLARE(ui_img_642941679);    // assets/extruder-4.png
LV_IMG_DECLARE(ui_img_642940654);    // assets/extruder-5.png
LV_IMG_DECLARE(ui_img_642948077);    // assets/extruder-6.png
LV_IMG_DECLARE(ui_img_642947052);    // assets/extruder-7.png
LV_IMG_DECLARE(ui_img_642946043);    // assets/extruder-8.png
LV_IMG_DECLARE(ui_img_642945018);    // assets/extruder-9.png
LV_IMG_DECLARE(ui_img_print_bar1_png);    // assets/print_bar1.png
LV_IMG_DECLARE(ui_img_print_bar2_png);    // assets/print_bar2.png

// UI INIT
void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
