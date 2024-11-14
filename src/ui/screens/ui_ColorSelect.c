// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: BoxTurtle

#include "../ui.h"

void ui_ColorSelect_screen_init(void)
{
    ui_ColorSelect = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ColorSelect, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Colorwheel1 = lv_colorwheel_create(ui_ColorSelect, true);
    lv_obj_set_width(ui_Colorwheel1, 150);
    lv_obj_set_height(ui_Colorwheel1, 150);
    lv_obj_set_align(ui_Colorwheel1, LV_ALIGN_CENTER);

    ui_ReturnColorSelect = lv_btn_create(ui_ColorSelect);
    lv_obj_set_width(ui_ReturnColorSelect, 100);
    lv_obj_set_height(ui_ReturnColorSelect, 50);
    lv_obj_set_x(ui_ReturnColorSelect, -261);
    lv_obj_set_y(ui_ReturnColorSelect, 56);
    lv_obj_set_align(ui_ReturnColorSelect, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ReturnColorSelect, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ReturnColorSelect, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    ui_object_set_themeable_style_property(ui_ReturnColorSelect, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                           _ui_theme_color_Blue);
    ui_object_set_themeable_style_property(ui_ReturnColorSelect, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                           _ui_theme_alpha_Blue);

    ui_Image3 = lv_img_create(ui_ReturnColorSelect);
    lv_img_set_src(ui_Image3, &ui_img_1470730272);
    lv_obj_set_width(ui_Image3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image3, -28);
    lv_obj_set_y(ui_Image3, 1);
    lv_obj_set_align(ui_Image3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label20 = lv_label_create(ui_ReturnColorSelect);
    lv_obj_set_width(ui_Label20, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label20, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label20, 2);
    lv_obj_set_y(ui_Label20, 1);
    lv_obj_set_align(ui_Label20, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label20, "Back");

    ui_SaveColorSelect = lv_btn_create(ui_ColorSelect);
    lv_obj_set_width(ui_SaveColorSelect, 100);
    lv_obj_set_height(ui_SaveColorSelect, 50);
    lv_obj_set_x(ui_SaveColorSelect, 250);
    lv_obj_set_y(ui_SaveColorSelect, 58);
    lv_obj_set_align(ui_SaveColorSelect, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_SaveColorSelect, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SaveColorSelect, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    ui_object_set_themeable_style_property(ui_SaveColorSelect, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_COLOR,
                                           _ui_theme_color_Blue);
    ui_object_set_themeable_style_property(ui_SaveColorSelect, LV_PART_MAIN | LV_STATE_DEFAULT, LV_STYLE_BG_OPA,
                                           _ui_theme_alpha_Blue);

    ui_Image4 = lv_img_create(ui_SaveColorSelect);
    lv_img_set_src(ui_Image4, &ui_img_complete_png);
    lv_obj_set_width(ui_Image4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Image4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Image4, 20);
    lv_obj_set_y(ui_Image4, 0);
    lv_obj_set_align(ui_Image4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label21 = lv_label_create(ui_SaveColorSelect);
    lv_obj_set_width(ui_Label21, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label21, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label21, -20);
    lv_obj_set_y(ui_Label21, 0);
    lv_obj_set_align(ui_Label21, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label21, "Save");

    lv_obj_add_event_cb(ui_ReturnColorSelect, ui_event_ReturnColorSelect, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SaveColorSelect, ui_event_SaveColorSelect, LV_EVENT_ALL, NULL);

}
