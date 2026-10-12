#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "esp_camera.h"

#include "board_esp32_s3_expboard.h"

static const char *TAG = "board_expboard";

/* ---------------- 全局句柄定义 ---------------- */
static esp_lcd_panel_io_handle_t s_lcd_io_handle = NULL;
static esp_lcd_panel_handle_t    s_lcd_panel_handle = NULL;
static bool s_camera_inited = false;
static bool s_lcd_inited = false;

/* ---------------- 1. 摄像头配置与初始化 ---------------- */
static const camera_config_t ov3660_cam_config = {
    .pin_pwdn     = -1,
    .pin_reset    = -1,
    .pin_xclk     = CAM_PIN_XCLK,     /* 14 */
    .pin_sccb_sda = CAM_PIN_SIOD,     /* 1 */
    .pin_sccb_scl = CAM_PIN_SIOC,     /* 2 */

    .pin_d7       = CAM_PIN_D7,       /* 18 */
    .pin_d6       = CAM_PIN_D6,       /* 17 */
    .pin_d5       = CAM_PIN_D5,       /* 16 */
    .pin_d4       = CAM_PIN_D4,       /* 15 */
    .pin_d3       = CAM_PIN_D3,       /* 7 */
    .pin_d2       = CAM_PIN_D2,       /* 6 */
    .pin_d1       = CAM_PIN_D1,       /* 5 */
    .pin_d0       = CAM_PIN_D0,       /* 4 */

    .pin_vsync    = CAM_PIN_VSYNC,    /* 3 */
    .pin_href     = CAM_PIN_HREF,     /* 8 */
    .pin_pclk     = CAM_PIN_PCLK,     /* 13 */

    .xclk_freq_hz = 20000000,
    .fb_location  = CAMERA_FB_IN_PSRAM,
    .pixel_format = PIXFORMAT_JPEG,
    .frame_size   = FRAMESIZE_QVGA,
    .jpeg_quality = 12,
    .fb_count     = 2,
    .grab_mode    = CAMERA_GRAB_WHEN_EMPTY,
};

bool board_camera_init(void) {
    if (s_camera_inited) return true;
    esp_err_t err = esp_camera_init(&ov3660_cam_config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Camera init failed with error 0x%x", err);
        return false;
    }
    s_camera_inited = true;
    ESP_LOGI(TAG, "Camera init successful");
    return true;
}

bool board_camera_deinit(void) {
    if (!s_camera_inited) return true;
    esp_err_t err = esp_camera_deinit();
    s_camera_inited = false;
    return (err == ESP_OK);
}

/* ---------------- 2. 屏幕配置与初始化 ---------------- */
static const spi_bus_config_t lcd_spi_bus = {
    .sclk_io_num     = LCD_PIN_CLK,      /* 19 */
    .mosi_io_num     = LCD_PIN_MOSI,     /* 20 */
    .miso_io_num     = -1,
    .quadwp_io_num   = -1,
    .quadhd_io_num   = -1,
    .max_transfer_sz = LCD_WIDTH * LCD_HEIGHT * 2,
};

static const esp_lcd_panel_io_spi_config_t lcd_io_config = {
    .cs_gpio_num       = LCD_PIN_CS,     /* 45 */
    .dc_gpio_num       = LCD_PIN_DC,     /* 47 */
    .spi_mode          = 0,
    .pclk_hz           = LCD_PCLK_HZ,    /* 40MHz */
    .trans_queue_depth = 10,
    .lcd_cmd_bits      = 8,
    .lcd_param_bits    = 8,
};

static const esp_lcd_panel_dev_config_t lcd_panel_config = {
    .reset_gpio_num = LCD_PIN_RST,       /* 21 */
    .color_space    = ESP_LCD_COLOR_SPACE_RGB,
    .bits_per_pixel = 16,
};

bool board_display_lcd_init(void) {
    if (s_lcd_inited) return true;

    /* 1. 初始化背光 GPIO38 并点亮 */
    gpio_config_t bl = {
        .pin_bit_mask = 1ULL << LCD_PIN_BL,
        .mode         = GPIO_MODE_OUTPUT,
    };
    gpio_config(&bl);
    gpio_set_level(LCD_PIN_BL, 1);

    /* 2. 初始化 SPI 总线 */
    esp_err_t ret = spi_bus_initialize(SPI2_HOST, &lcd_spi_bus, SPI_DMA_CH_AUTO);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "LCD SPI bus initialize failed");
        return false;
    }

    /* 3. 创建 Panel IO */
    ret = esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPI2_HOST, &lcd_io_config, &s_lcd_io_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "New panel io spi failed");
        return false;
    }

    /* 4. 创建 ST7789 面板驱动并初始化 */
    ret = esp_lcd_new_panel_st7789(s_lcd_io_handle, &lcd_panel_config, &s_lcd_panel_handle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "New panel st7789 failed");
        return false;
    }

    esp_lcd_panel_reset(s_lcd_panel_handle);
    esp_lcd_panel_init(s_lcd_panel_handle);
    esp_lcd_panel_disp_on_off(s_lcd_panel_handle, true);

    s_lcd_inited = true;
    ESP_LOGI(TAG, "LCD ST7789 init successful");
    return true;
}

bool board_display_lcd_deinit(void) {
    if (!s_lcd_inited) return true;
    gpio_set_level(LCD_PIN_BL, 0);
    if (s_lcd_panel_handle) esp_lcd_panel_del(s_lcd_panel_handle);
    if (s_lcd_io_handle) esp_lcd_panel_io_del(s_lcd_io_handle);
    spi_bus_free(SPI2_HOST);
    s_lcd_inited = false;
    return true;
}

/* ---------------- 3. 参数导出接口供 board_manager 调用 ---------------- */
void board_get_camera_paths(const char **dev_path, const char **meta_path) {
    if (dev_path)  *dev_path  = CAM_DEV_PATH;
    if (meta_path) *meta_path = CAM_META_PATH;
}

void board_get_display_lcd_params(void **panel_handle, void **io_handle, int *w, int *h, int *panel_if) {
    if (panel_handle) *panel_handle = (void *)s_lcd_panel_handle;
    if (io_handle)
