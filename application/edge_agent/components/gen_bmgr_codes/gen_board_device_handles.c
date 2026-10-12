/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO., LTD
 * SPDX-License-Identifier: LicenseRef-Espressif-Modified-MIT
 *
 * Auto-generated device handle definition file
 * DO NOT MODIFY THIS FILE MANUALLY
 *
 * See LICENSE file for details.
 */

#include <stddef.h>
#include "esp_board_device.h"
#include "dev_audio_codec.h"
#include "dev_custom.h"
#include "dev_display_lcd.h"

// Device handle array
esp_board_device_handle_t g_esp_board_device_handles[] = {
    {
        .next = &g_esp_board_device_handles[1],
        .name = "led_strip",
        .chip = "ws2812",
        .type = "custom",
        .device_handle = NULL,
        .init = dev_custom_init,
        .deinit = dev_custom_deinit
    },
    {
        .next = &g_esp_board_device_handles[2],
        .name = "fake_audio_dac",
        .chip = "none",
        .type = "audio_codec",
        .device_handle = NULL,
        .init = dev_audio_codec_init,
        .deinit = dev_audio_codec_deinit
    },
    {
        .next = &g_esp_board_device_handles[3],
        .name = "camera",
        .chip = NULL,
        .type = "custom",
        .device_handle = NULL,
        .init = dev_custom_init,
        .deinit = dev_custom_deinit
    },
    {
        .next = &g_esp_board_device_handles[4],
        .name = "audio_dac",
        .chip = NULL,
        .type = "custom",
        .device_handle = NULL,
        .init = dev_custom_init,
        .deinit = dev_custom_deinit
    },
    {
        .next = &g_esp_board_device_handles[5],
        .name = "audio_adc",
        .chip = NULL,
        .type = "custom",
        .device_handle = NULL,
        .init = dev_custom_init,
        .deinit = dev_custom_deinit
    },
    {
        .next = NULL,
        .name = "display_lcd",
        .chip = "st7789",
        .type = "display_lcd",
        .device_handle = NULL,
        .init = dev_display_lcd_init,
        .deinit = dev_display_lcd_deinit
    },
};
