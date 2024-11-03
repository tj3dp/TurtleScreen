// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: BoxTurtle

#include "../ui.h"

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Container2 = lv_obj_create(ui_Screen1);
    lv_obj_remove_style_all(ui_Container2);
    lv_obj_set_width(ui_Container2, 100);
    lv_obj_set_height(ui_Container2, 50);
    lv_obj_set_x(ui_Container2, -265);
    lv_obj_set_y(ui_Container2, -59);
    lv_obj_set_align(ui_Container2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Container2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label4 = lv_label_create(ui_Container2);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label4, -3);
    lv_obj_set_y(ui_Label4, -13);
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "Current Leg");

    ui_Label5 = lv_label_create(ui_Container2);
    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label5, 0);
    lv_obj_set_y(ui_Label5, 6);
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "Leg2");

    ui_Panel1 = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_Panel1, 195);
    lv_obj_set_height(ui_Panel1, 51);
    lv_obj_set_x(ui_Panel1, 1);
    lv_obj_set_y(ui_Panel1, 0);
    lv_obj_set_align(ui_Panel1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label6 = lv_label_create(ui_Panel1);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    /// 1
    lv_label_set_text(ui_Label6, "Tool Loaded");

    ui_Label7 = lv_label_create(ui_Panel1);
    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label7, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_Label7, "False");

    uic_Label5 = ui_Label5;

}
