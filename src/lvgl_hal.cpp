#include "lvgl_hal.h"
#include "ui/ui.h"

lv_obj_t *ui_cartext = NULL;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *buf;
static lv_color_t *buf1;
static bool hw_setup = false;
static bool lv_initialized = false;

void usr_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    #ifdef LCD_SPI_DMA
        char i = 0;
		while (get_lcd_spi_dma_write())
		{
			i = i >> 1;
			lcd_PushColors(0, 0, 0, 0, NULL);
		}
    #endif
      lcd_PushColors(area->x1, area->y1, w, h, (uint16_t *)&color_p->full);

    #ifdef LCD_SPI_DMA

    #else
        lv_disp_flush_ready(disp);
    #endif
}
uint8_t read_touchpad_cmd[11] = {0xb5, 0xab, 0xa5, 0x5a, 0x0, 0x0, 0x0, 0x8};
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
    uint8_t buff[20] = {0};

    Wire.beginTransmission(0x3B);
    Wire.write(read_touchpad_cmd, 8);
    Wire.endTransmission();
    Wire.requestFrom(0x3B, 8);
    while (!Wire.available());
    Wire.readBytes(buff, 8);

    uint16_t pointX;
    uint16_t pointY;
    uint16_t type = 0;

    type = AXS_GET_GESTURE_TYPE(buff);
    pointX = AXS_GET_POINT_X(buff,0);
    pointY = AXS_GET_POINT_Y(buff,0);

    if (!type && (pointX || pointY)) {
        pointX = (640-pointX);
        if(pointX > 640) pointX = 640;
        if(pointY > 180) pointY = 180;
        data->state = LV_INDEV_STATE_PR;
        data->point.x = pointY;
        data->point.y = pointX;

        char buf[20] = {0};
        sprintf(buf, "(%d, %d)", data->point.x, data->point.y);
        if(ui_cartext != NULL)
        lv_label_set_text(ui_cartext, buf);
    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }
}

static int8_t aw9346_from_light = -1;


void tft_backlight_init(void) {
    pinMode(LCD_BL_PIN, OUTPUT);
    digitalWrite(LCD_BL_PIN, LOW);
    delay(3); // > 2.5ms for shutdown
    aw9346_from_light = 0;
}
void tft_set_backlight(int8_t aw9346_to_light) {
    if (aw9346_to_light > 16) aw9346_to_light = 16;
    if (aw9346_to_light < 0) aw9346_to_light = 0;
    if (aw9346_from_light == aw9346_to_light) return;

    if (aw9346_to_light == 0) {
        digitalWrite(LCD_BL_PIN, LOW);
        delay(3); // > 2.5ms for shutdown
        aw9346_from_light = 0;
        return;
    }
    if (aw9346_from_light <= 0) {
        digitalWrite(LCD_BL_PIN, HIGH);
        delayMicroseconds(25); // > 20us for poweron
        aw9346_from_light = 16;
    }

    if (aw9346_from_light < aw9346_to_light)
        aw9346_from_light += 16;

    int8_t num = aw9346_from_light - aw9346_to_light;

    for (int8_t i = 0; i < num; i++) {
        digitalWrite(LCD_BL_PIN, LOW);
        delayMicroseconds(1); // 0.5us < T_low < 500us
        digitalWrite(LCD_BL_PIN, HIGH);
        delayMicroseconds(1); // 0.5us < T_high
    }

    aw9346_from_light = aw9346_to_light;
}


lv_indev_t * ts_cst816s_indev;
void lvgl_hal_init(void) {
    if (!hw_setup) {
        pinMode(TOUCH_RES, OUTPUT);
        digitalWrite(TOUCH_RES, HIGH); delay(2);
        digitalWrite(TOUCH_RES, LOW); delay(10);
        digitalWrite(TOUCH_RES, HIGH); delay(2);

        Wire.begin(TOUCH_IICSDA, TOUCH_IICSCL);

        pinMode(LCD_BL_PIN , OUTPUT);
        digitalWrite(LCD_BL_PIN , HIGH);

        axs15231_init();
        hw_setup = true;
    }

    if (!lv_initialized) {
        lv_init();
        lv_initialized = true;
    }

    size_t buffer_size = sizeof(lv_color_t) * EXAMPLE_LCD_H_RES * EXAMPLE_LCD_V_RES;

    if (buf == nullptr) {
        buf = (lv_color_t *)ps_malloc(buffer_size);
        if (buf == NULL) {
            Serial.println("Failed to allocate buf");
            return;
        }
    }

    if (buf1 == nullptr) {
        buf1 = (lv_color_t *)ps_malloc(buffer_size);
        if (buf1 == NULL) {
            Serial.println("Failed to allocate buf1");
            return;
        }
    }

    lv_disp_draw_buf_init(&draw_buf, buf, buf1, EXAMPLE_LCD_H_RES * EXAMPLE_LCD_V_RES);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    disp_drv.hor_res = EXAMPLE_LCD_H_RES;
    disp_drv.ver_res = EXAMPLE_LCD_V_RES;
    disp_drv.flush_cb = usr_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.sw_rotate = 1;
    disp_drv.rotated = LV_DISP_ROT_90;
    disp_drv.full_refresh = 1;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    lv_obj_set_style_bg_color(lv_scr_act(), LV_COLOR_MAKE(0, 0, 0), LV_STATE_DEFAULT);
    lv_obj_invalidate(lv_scr_act());

    Serial.println("Finished LVGL startup");
}

