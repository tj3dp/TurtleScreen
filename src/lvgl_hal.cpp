#include "lvgl_hal.h"
//#include "ui.h"

lv_obj_t *ui_cartext = NULL;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *buf;
static lv_color_t *buf1;
static bool hw_setup = false;
static bool lv_initialized = false;


#ifdef WT32_SC01_PLUS_LGFX
    #include <LGFX_WT32-SC01-PLUS-DISPLAY.hpp>
    #include <LGFX_TFT_eSPI.hpp>
    static LGFX tft; // declare display variable
    #define touch tft
    #define LGFX_TOUCH
#endif

#ifdef SUNTON_ESP32_320_240
    #include <LGFX_SUNTON_ESP32_320_240.hpp>
    #define LGFX Sunton_ESP32_320_240
    static LGFX tft; // declare display variable
    #define touch tft
    #define LGFX_TOUCH
#endif


#define DISP_BUF_SIZE (EXAMPLE_LCD_H_RES * 10)
static lv_color_t disp_buf[DISP_BUF_SIZE];

void usr_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) 
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

#if defined(WT32_SC01_PLUS_LGFX) or defined(SUNTON_ESP32_320_240)
    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)&color_p->full, w * h, false);
    tft.endWrite();
    lv_disp_flush_ready(disp);
#else
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
#endif
}

uint8_t read_touchpad_cmd[11] = {0xb5, 0xab, 0xa5, 0x5a, 0x0, 0x0, 0x0, 0x8};
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {

#if defined(WT32_SC01_PLUS_LGFX) or defined(SUNTON_ESP32_320_240)
    uint16_t touchX, touchY;
    static uint16_t last_x = 0xffff, last_y = 0xffff;

    uint8_t gesture = 0;
    bool touched;

    #ifdef LGFX_TOUCH
        touched = touch.getTouch(&touchX, &touchY);
    #else
        touched = touch.getTouch(&touchX, &touchY, &gesture);
    #endif
    //Serial.printf("touch   (x,y,g): (%03d,%03d,%3d)\n", touchX, touchY, gesture);

    if (!touched) 
    {
        if (last_x != 0xffff) 
        {
            data->state = LV_INDEV_STATE_REL;
            data->point.x = last_x;
            data->point.y = last_y;
            //Serial.printf("release (x,y,g): (%03d,%03d,%3d)\n", touchX, touchY, gesture);
            last_x = 0xffff;
        }
    } 
    else 
    {
        data->state = LV_INDEV_STATE_PR;
        last_x = data->point.x = touchX;
        last_y = data->point.y = touchY;
        //Serial.printf("touch   (x,y,g): (%03d,%03d,%3d)\n", touchX, touchY, gesture);
    }
#else
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
#endif
}


#ifdef T3DISPLAY
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
#endif


#ifdef T3DISPLAY
    lv_indev_t * ts_cst816s_indev;
#endif

void lvgl_hal_init(void) {
    static lv_disp_drv_t disp_drv;
#if defined(WT32_SC01_PLUS_LGFX) or defined(SUNTON_ESP32_320_240)
    if (!hw_setup) 
    {
        tft.init();
        #ifdef WT32_SC01_PLUS_LGFX
            tft.setRotation(1);
        #else
            tft.setRotation(0);
        #endif
        #ifndef LGFX_TOUCH
            touch.begin();
        #endif
        hw_setup = true;
    }
#else
    static int8_t aw9346_from_light = -1;
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
#endif

    if (!lv_initialized) {
        lv_init();
        lv_initialized = true;
    }


#if 0
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
#else
    lv_disp_draw_buf_init(&draw_buf, disp_buf, NULL, DISP_BUF_SIZE);
#endif
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = EXAMPLE_LCD_H_RES;
    disp_drv.ver_res = EXAMPLE_LCD_V_RES;
    disp_drv.flush_cb = usr_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    #ifdef T3DISPLAY
        disp_drv.sw_rotate = 1;
        disp_drv.rotated = LV_DISP_ROT_90;
    #endif
    //disp_drv.full_refresh = 1;
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
