/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO., LTD
 * SPDX-License-Identifier: LicenseRef-Espressif-Modified-MIT
 *
 * Auto-generated device configuration file
 * DO NOT MODIFY THIS FILE MANUALLY
 *
 * See LICENSE file for details.
 */

#include <stdlib.h>
#include "esp_board_device.h"
#include "dev_audio_codec.h"
#include "dev_custom.h"
#include "dev_display_lcd.h"
#include "gen_board_device_custom.h"

// Device configuration structures
const static dev_custom_led_strip_config_t esp_bmgr_led_strip_cfg = {
    .name = "led_strip",
    .type = "custom",
    .chip = "ws2812",
    .max_leds = 1,
    .peripheral_count = 1,
    .peripheral_name = "rmt_tx",
};

const static dev_audio_codec_config_t esp_bmgr_fake_audio_dac_cfg = {
    .name = "fake_audio_dac",
    .chip = "none",
    .type = "audio_codec",
    .data_if_type = 0,
    .adc_enabled = false,
    .adc_max_channel = 0,
    .adc_channel_mask = 0x3,
    .adc_channel_labels = "",
    .adc_init_gain = 0,
    .dac_enabled = false,
    .dac_max_channel = 0,
    .dac_channel_mask = 0x0,
    .dac_init_gain = 0,
    .pa_cfg = {
        .name = NULL,
        .port = -1,
        .active_level = 0,
        .gain = 0.0,
    },
    .i2c_cfg = {
        .name = NULL,
        .port = 0,
        .address = 0,
        .frequency = 0,
    },
    .i2s_cfg = {
        .name = "i2s_audio_out",
        .port = 0,
        .clk_src = 0,
        .tx_aux_out_io = -1,
        .tx_aux_out_line = 0,
        .tx_aux_out_invert = false,
    },
    .adc_cfg = {
        .periph_name = NULL,
        .sample_rate_hz = 0,
        .max_store_buf_size = 0,
        .conv_frame_size = 0,
        .conv_mode = 0,
        .format = 0,
        .pattern_num = 0,
        .cfg_mode = 0,
        .cfg = {
            .single_unit = {
                .unit_id = 0,
                .atten = 0,
                .bit_width = 0,
                .channel_id = {},
            },
        },
    },
    .metadata = NULL,
    .metadata_size = 0,
    .mclk_enabled = false,
    .aec_enabled = false,
    .eq_enabled = false,
    .alc_enabled = false,
};

const static dev_custom_camera_config_t esp_bmgr_camera_cfg = {
    .name = "camera",
    .type = "custom",
    .chip = "unknown",
};

const static dev_custom_audio_dac_config_t esp_bmgr_audio_dac_cfg = {
    .name = "audio_dac",
    .type = "custom",
    .chip = "unknown",
    .sample_rate_hz = 16000,
};

const static dev_custom_audio_adc_config_t esp_bmgr_audio_adc_cfg = {
    .name = "audio_adc",
    .type = "custom",
    .chip = "unknown",
    .sample_rate_hz = 16000,
};

const static dev_display_lcd_config_t esp_bmgr_display_lcd_cfg = {
    .name = "display_lcd",
    .chip = "st7789",
    .sub_type = "spi",
    .lcd_width = 320,
    .lcd_height = 240,
    .swap_xy = true,
    .mirror_x = false,
    .mirror_y = true,
    .need_reset = true,
    .invert_color = true,
    .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
    .data_endian = LCD_RGB_DATA_ENDIAN_BIG,
    .bits_per_pixel = 16,
    .sub_cfg = {
        .spi = {
            .spi_name = "spi_display",
            .panel_config = {
                .reset_gpio_num = 6,
                .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
                .data_endian = LCD_RGB_DATA_ENDIAN_BIG,
                .bits_per_pixel = 16,
                .flags = {
                    .reset_active_high = false,
                },
                .vendor_config = NULL,
            },
            .io_spi_config = {
                .cs_gpio_num = 15,
                .dc_gpio_num = 7,
                .spi_mode = 0,
                .pclk_hz = 40000000,
                .trans_queue_depth = 2,
                .lcd_cmd_bits = 8,
                .lcd_param_bits = 8,
                .cs_ena_pretrans = 0,
                .cs_ena_posttrans = 0,
                .flags = {
                    .dc_high_on_cmd = false,
                    .dc_low_on_data = false,
                    .dc_low_on_param = false,
                    .octal_mode = false,
                    .quad_mode = false,
                    .sio_mode = false,
                    .lsb_first = false,
                    .cs_high_active = false,
                },
            },
        },
    },
};

// Device descriptor array

const esp_board_device_desc_t g_esp_board_devices[] = {
    {
        .next = &g_esp_board_devices[1],
        .name = "led_strip",
        .chip = "ws2812",
        .type = "custom",
        .sub_type = NULL,
        .cfg = &esp_bmgr_led_strip_cfg,
        .cfg_size = sizeof(esp_bmgr_led_strip_cfg),
        .init_skip = true,
        .depends_on = NULL,
        .depends_on_num = 0,
    },
    {
        .next = &g_esp_board_devices[2],
        .name = "fake_audio_dac",
        .chip = "none",
        .type = "audio_codec",
        .sub_type = NULL,
        .cfg = &esp_bmgr_fake_audio_dac_cfg,
        .cfg_size = sizeof(esp_bmgr_fake_audio_dac_cfg),
        .init_skip = true,
        .depends_on = NULL,
        .depends_on_num = 0,
    },
    {
        .next = &g_esp_board_devices[3],
        .name = "camera",
        .chip = NULL,
        .type = "custom",
        .sub_type = NULL,
        .cfg = &esp_bmgr_camera_cfg,
        .cfg_size = sizeof(esp_bmgr_camera_cfg),
        .init_skip = false,
        .depends_on = NULL,
        .depends_on_num = 0,
    },
    {
        .next = &g_esp_board_devices[4],
        .name = "audio_dac",
        .chip = NULL,
        .type = "custom",
        .sub_type = NULL,
        .cfg = &esp_bmgr_audio_dac_cfg,
        .cfg_size = sizeof(esp_bmgr_audio_dac_cfg),
        .init_skip = false,
        .depends_on = NULL,
        .depends_on_num = 0,
    },
    {
        .next = &g_esp_board_devices[5],
        .name = "audio_adc",
        .chip = NULL,
        .type = "custom",
        .sub_type = NULL,
        .cfg = &esp_bmgr_audio_adc_cfg,
        .cfg_size = sizeof(esp_bmgr_audio_adc_cfg),
        .init_skip = false,
        .depends_on = NULL,
        .depends_on_num = 0,
    },
    {
        .next = NULL,
        .name = "display_lcd",
        .chip = "st7789",
        .type = "display_lcd",
        .sub_type = "spi",
        .cfg = &esp_bmgr_display_lcd_cfg,
        .cfg_size = sizeof(esp_bmgr_display_lcd_cfg),
        .init_skip = false,
        .depends_on = NULL,
        .depends_on_num = 0,
    },
};
