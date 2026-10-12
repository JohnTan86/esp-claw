/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO., LTD
 * SPDX-License-Identifier: LicenseRef-Espressif-Modified-MIT
 *
 * Auto-generated peripheral configuration file
 * DO NOT MODIFY THIS FILE MANUALLY
 *
 * See LICENSE file for details.
 */

#include <stdlib.h>
#include "esp_board_periph.h"
#include "driver/i2c_master.h"
#include "driver/i2c_types.h"
#include "hal/gpio_types.h"
#include "periph_i2s.h"
#include "periph_ledc.h"
#include "periph_rmt.h"
#include "periph_spi.h"

// Peripheral configuration structures
const static periph_rmt_config_t esp_bmgr_rmt_tx_cfg = {
    .role = ESP_BOARD_PERIPH_ROLE_TX,
    .channel_config = {
        .tx = {
            .gpio_num = 38,
            .clk_src = RMT_CLK_SRC_DEFAULT,
            .resolution_hz = 10000000,
            .mem_block_symbols = 64,
            .trans_queue_depth = 4,
            .intr_priority = 1,
            .flags = {
                .invert_out = false,
                .with_dma = true,
                .io_loop_back = false,
                .io_od_mode = false,
            },
        },
    },
};

const static i2c_master_bus_config_t esp_bmgr_i2c_master_cfg = {
    .i2c_port = I2C_NUM_0,
    .sda_io_num = 2,
    .scl_io_num = 3,
    .glitch_ignore_cnt = 7,
    .intr_priority = 1,
    .trans_queue_depth = 0,
    .flags = {
        .enable_internal_pullup = true,
    },
    .clk_source = I2C_CLK_SRC_DEFAULT,
};

const static periph_i2s_config_t esp_bmgr_i2s_audio_out_cfg = {
    .port = I2S_NUM_0,
    .role = I2S_ROLE_MASTER,
    .mode = I2S_COMM_MODE_PDM,
    .direction = I2S_DIR_TX,
    .i2s_cfg = {
        .pdm_tx = {
            .clk_cfg = {
                .sample_rate_hz = 16000,
                .clk_src = I2S_CLK_SRC_DEFAULT,
                .mclk_multiple = I2S_MCLK_MULTIPLE_256,
                .up_sample_fp = 960,
                .up_sample_fs = 441,
                .bclk_div = 8,
            },
            .slot_cfg = {
                .data_bit_width = I2S_DATA_BIT_WIDTH_16BIT,
                .slot_bit_width = I2S_SLOT_BIT_WIDTH_AUTO,
                .slot_mode = I2S_SLOT_MODE_MONO,
                .sd_prescale = 0,
                .sd_scale = I2S_PDM_SIG_SCALING_MUL_4,
                .hp_scale = I2S_PDM_SIG_SCALING_MUL_4,
                .lp_scale = I2S_PDM_SIG_SCALING_MUL_4,
                .sinc_scale = I2S_PDM_SIG_SCALING_MUL_4,
                .line_mode = I2S_PDM_TX_ONE_LINE_CODEC,
                .hp_en = false,
                .hp_cut_off_freq_hz = 35.5,
                .sd_dither = 0,
                .sd_dither2 = 1,
            },
            .gpio_cfg = {
                .clk = -1,
                .dout = 9,
                .invert_flags = {
                    .clk_inv = false,
                },
            },
        },
    },
};

static periph_spi_config_t esp_bmgr_spi_display_cfg = {
    .spi_port = SPI3_HOST,
    .spi_bus_config = {
        .mosi_io_num = 5,
        .miso_io_num = -1,
        .sclk_io_num = 4,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .data4_io_num = -1,
        .data5_io_num = -1,
        .data6_io_num = -1,
        .data7_io_num = -1,
        .max_transfer_sz = 6400,
        .flags = 0,
        .isr_cpu_id = ESP_INTR_CPU_AFFINITY_AUTO,
        .intr_flags = 0,
    },
};

const static periph_ledc_config_t esp_bmgr_ledc_backlight_cfg = {
    .handle = {
        .channel = LEDC_CHANNEL_0,
        .speed_mode = LEDC_LOW_SPEED_MODE,
    },
    .gpio_num = 16,
    .duty = 0,
    .freq_hz = 5000,
    .duty_resolution = LEDC_TIMER_10_BIT,
    .timer_sel = LEDC_TIMER_0,
    .sleep_mode = LEDC_SLEEP_MODE_NO_ALIVE_NO_PD,
    .output_invert = true,
};

// Peripheral descriptor array
const esp_board_periph_desc_t g_esp_board_peripherals[] = {
    {
        .next = &g_esp_board_peripherals[1],
        .name = "rmt_tx",
        .type = "rmt",
        .format = NULL,
        .role = ESP_BOARD_PERIPH_ROLE_TX,
        .cfg = &esp_bmgr_rmt_tx_cfg,
        .cfg_size = sizeof(esp_bmgr_rmt_tx_cfg),
        .id = 0,
    },
    {
        .next = &g_esp_board_peripherals[2],
        .name = "i2c_master",
        .type = "i2c",
        .format = NULL,
        .role = ESP_BOARD_PERIPH_ROLE_MASTER,
        .cfg = &esp_bmgr_i2c_master_cfg,
        .cfg_size = sizeof(esp_bmgr_i2c_master_cfg),
        .id = 0,
    },
    {
        .next = &g_esp_board_peripherals[3],
        .name = "i2s_audio_out",
        .type = "i2s",
        .format = "pdm-out",
        .role = ESP_BOARD_PERIPH_ROLE_MASTER,
        .cfg = &esp_bmgr_i2s_audio_out_cfg,
        .cfg_size = sizeof(esp_bmgr_i2s_audio_out_cfg),
        .id = 0,
    },
    {
        .next = &g_esp_board_peripherals[4],
        .name = "spi_display",
        .type = "spi",
        .format = NULL,
        .role = ESP_BOARD_PERIPH_ROLE_MASTER,
        .cfg = &esp_bmgr_spi_display_cfg,
        .cfg_size = sizeof(esp_bmgr_spi_display_cfg),
        .id = 0,
    },
    {
        .next = NULL,
        .name = "ledc_backlight",
        .type = "ledc",
        .format = NULL,
        .role = ESP_BOARD_PERIPH_ROLE_NONE,
        .cfg = &esp_bmgr_ledc_backlight_cfg,
        .cfg_size = sizeof(esp_bmgr_ledc_backlight_cfg),
        .id = 0,
    },
};
