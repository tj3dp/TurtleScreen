#include "lvgl_hal.h"
#include "ui/ui.h"
#ifndef T3DISPLAY
TFT_eSPI tft_gc9a01 = TFT_eSPI();
#endif
#ifdef CST816S_SUPPORT
extern TwoWire i2c0;
CST816S ts_cst816s = CST816S(CST816S_RST_PIN, CST816S_IRQ_PIN, &i2c0);
#endif

/* Display flushing */
#ifndef T3DISPLAY
void usr_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    // usr fill color
    tft_gc9a01.startWrite();
    tft_gc9a01.setAddrWindow(area->x1, area->y1, w, h);
    tft_gc9a01.pushColors((uint16_t *)&color_p->full, w * h, true);
    tft_gc9a01.endWrite();

    lv_disp_flush_ready(disp);
}
#endif

#ifdef T3DISPLAY
lv_obj_t *ui_cartext = NULL;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *buf;
static lv_color_t *buf1;
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
#endif
#ifdef CST816S_SUPPORT
void touch_idle_time_clear(void);
void usr_touchpad_read(struct _lv_indev_drv_t * indev_drv, lv_indev_data_t * data) {
    static touch_event_t event;
    if(ts_cst816s.ready()) {
        ts_cst816s.getTouch(&event);
    }
    if(event.finger) {
        data->state = LV_INDEV_STATE_PR;
        /*Set the coordinates*/
        data->point.x = event.x;
        data->point.y = event.y;
        touch_idle_time_clear();
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}
#endif

static int8_t aw9346_from_light = -1;

void lvgl_ui_task(void * parameter) {
    lvgl_hal_init();
    ui_init();
}

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

void tft_fps_test(void) {
    uint8_t test_sec = 3;
    uint32_t ms = millis() + test_sec * 1000;
    uint32_t frames = 0;
    #ifndef T3DISPLAY
    const uint32_t test_colors[] = {TFT_RED, TFT_GREEN, TFT_BLUE};
    while(ms > millis()) {
        tft_gc9a01.fillScreen(test_colors[frames % (sizeof(test_colors) / sizeof(test_colors[0]))]);
        frames++;
    }
    #endif
    Serial.println("\r\n******** lcd fps test *****\r\n");
    Serial.print("fps=");
    Serial.println(frames / test_sec, DEC);
    Serial.print("test_sec=");
    Serial.println(test_sec, DEC);
    Serial.println("\r\n***************************\r\n");
}

lv_indev_t * ts_cst816s_indev;
void lvgl_hal_init(void) {
#ifdef CST816S_SUPPORT
    // touch screen
    ts_cst816s.begin();
    ts_cst816s.setReportRate(2); // 20ms
    ts_cst816s.setReportMode(0x60); // touch + gesture generated interrupt
    ts_cst816s.setMotionMask(0); // disable motion
    ts_cst816s.setAutoRst(0); // disable auto reset
    ts_cst816s.setLongRst(0); // disable long press reset
    ts_cst816s.setDisAutoSleep(1); // disable auto sleep
#endif

    // display.

    #ifndef T3DISPLAY
    tft_gc9a01.begin();
    tft_gc9a01.invertDisplay(1);
    // tft_gc9a01.setRotation(2);

    tft_gc9a01.fillScreen(TFT_BLACK);
    tft_backlight_init();
    delay(50);
    tft_set_backlight(16);
    #endif
    #ifdef T3DISPLAY
    pinMode(TOUCH_RES, OUTPUT);
    digitalWrite(TOUCH_RES, HIGH);delay(2);
    digitalWrite(TOUCH_RES, LOW);delay(10);
    digitalWrite(TOUCH_RES, HIGH);delay(2);

    Wire.begin(TOUCH_IICSDA, TOUCH_IICSCL);

    pinMode(LCD_BL_PIN , OUTPUT);
    digitalWrite(LCD_BL_PIN , HIGH);

    axs15231_init();
    
    #endif

    // tft_fps_test();
    #ifndef T3DISPLAY
    // must static
    static lv_disp_draw_buf_t draw_buf;
    static lv_color_t *color_buf = (lv_color_t *)LV_MEM_CUSTOM_ALLOC(TFT_WIDTH * TFT_HEIGHT * sizeof(lv_color_t));
    lv_init();
    lv_disp_draw_buf_init(&draw_buf, color_buf, NULL, TFT_WIDTH * TFT_HEIGHT);

    /*Initialize the display*/
    // must static
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = TFT_WIDTH;
    disp_drv.ver_res = TFT_HEIGHT;
    disp_drv.flush_cb = usr_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);
    // lv_disp_set_rotation(NULL, LV_DISP_ROT_180);
    #endif
    #ifdef T3DISPLAY
        lv_init();
    size_t buffer_size =
        sizeof(lv_color_t) * EXAMPLE_LCD_H_RES * EXAMPLE_LCD_V_RES;
    buf = (lv_color_t *)ps_malloc(buffer_size);
    if (buf == NULL) {
      while (1) {
        Serial.println("buf NULL");
        delay(500);
      }
    }

    buf1 = (lv_color_t *)ps_malloc(buffer_size);
    if (buf1 == NULL) {
      while (1) {
        Serial.println("buf NULL");
        delay(500);
      }
    }

    lv_disp_draw_buf_init(&draw_buf, buf, buf1, buffer_size);
    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = EXAMPLE_LCD_H_RES;
    disp_drv.ver_res = EXAMPLE_LCD_V_RES;
    disp_drv.flush_cb = usr_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    disp_drv.sw_rotate = 1;             //If you turn on software rotation, Do not update or replace LVGL
    disp_drv.rotated = LV_DISP_ROT_90;  
    disp_drv.full_refresh = 1;          //full_refresh must be 1
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);
    
    #endif

#ifdef CST816S_SUPPORT
    /* touch screen */
    // must static
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);      /*Basic initialization*/
    indev_drv.gesture_limit = 1;
    indev_drv.gesture_min_velocity = 1;
    indev_drv.type = LV_INDEV_TYPE_POINTER;                 /*See below.*/
    indev_drv.read_cb = usr_touchpad_read;              /*See below.*/
    /*Register the driver in LVGL and save the created input device object*/
    ts_cst816s_indev = lv_indev_drv_register(&indev_drv);
#endif

    /* set background color to black (default white) */
    lv_obj_set_style_bg_color(lv_scr_act(), LV_COLOR_MAKE(0, 0, 0), LV_STATE_DEFAULT);
    Serial.println("Finished LVGL startup\n");
}
