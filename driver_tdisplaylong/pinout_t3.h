#pragma once

#ifdef T3DISPLAY

/***********************config*************************/
#define LCD_USB_QSPI_DREVER   1

#define SPI_FREQUENCY           32000000
#define TFT_SPI_MODE          SPI_MODE0
#define TFT_SPI_HOST          SPI2_HOST

/***********************config*************************/

#define TFT_WIDTH             180
#define TFT_HEIGHT            640

#ifdef TFT_WIDTH
#define EXAMPLE_LCD_H_RES     TFT_WIDTH
#else
#define EXAMPLE_LCD_H_RES     180
#endif
#ifdef TFT_HEIGHT
#define EXAMPLE_LCD_V_RES     TFT_HEIGHT
#else
#define EXAMPLE_LCD_V_RES     640
#endif
#define LVGL_LCD_BUF_SIZE     (EXAMPLE_LCD_H_RES * EXAMPLE_LCD_V_RES)

#define SEND_BUF_SIZE         (28800/2) //16bit(RGB565)

#define TFT_QSPI_CS           12
#define TFT_QSPI_SCK          17
#define TFT_QSPI_D0           13
#define TFT_QSPI_D1           18
#define TFT_QSPI_D2           21
#define TFT_QSPI_D3           14
#define TFT_QSPI_RST          16
#define LCD_BL_PIN                1


#define PIN_BAT_VOLT          2

#define BOOT_PIN          0
#define PIN_BUTTON_2          21

#define SPI_SD_CS            38
#define SPI_SD_MOSI           39
#define SPI_SD_MISO           41
#define SPI_SD_SCLK           40


#define TOUCH_IICSCL 10
#define TOUCH_IICSDA 15
#define TOUCH_INT    11
#define TOUCH_RES    16

//uint8_t ALS_ADDRESS = 0x3B;

#define AXS_TOUCH_ONE_POINT_LEN 6
#define AXS_TOUCH_BUF_HEAD_LEN  2

#define AXS_TOUCH_GESTURE_POS 0
#define AXS_TOUCH_POINT_NUM   1
#define AXS_TOUCH_EVENT_POS   2
#define AXS_TOUCH_X_H_POS     2
#define AXS_TOUCH_X_L_POS     3
#define AXS_TOUCH_ID_POS      4
#define AXS_TOUCH_Y_H_POS     4
#define AXS_TOUCH_Y_L_POS     5
#define AXS_TOUCH_WEIGHT_POS  6
#define AXS_TOUCH_AREA_POS    7

#define AXS_GET_POINT_NUM(buf)                buf[AXS_TOUCH_POINT_NUM]
#define AXS_GET_GESTURE_TYPE(buf)             buf[AXS_TOUCH_GESTURE_POS]
#define AXS_GET_POINT_X(buf, point_index)     (((uint16_t)(buf[AXS_TOUCH_ONE_POINT_LEN * point_index + AXS_TOUCH_X_H_POS] & 0x0F) << 8) + (uint16_t)buf[AXS_TOUCH_ONE_POINT_LEN * point_index + AXS_TOUCH_X_L_POS])
#define AXS_GET_POINT_Y(buf, point_index)     (((uint16_t)(buf[AXS_TOUCH_ONE_POINT_LEN * point_index + AXS_TOUCH_Y_H_POS] & 0x0F) << 8) + (uint16_t)buf[AXS_TOUCH_ONE_POINT_LEN * point_index + AXS_TOUCH_Y_L_POS])
#define AXS_GET_POINT_EVENT(buf, point_index) (buf[AXS_TOUCH_ONE_POINT_LEN * point_index + AXS_TOUCH_EVENT_POS] >> 6)

#endif