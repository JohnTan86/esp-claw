/*
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO., LTD
 * SPDX-License-Identifier: LicenseRef-Espressif-Modified-MIT
 *
 * Auto-generated custom device structure definitions
 * DO NOT MODIFY THIS FILE MANUALLY
 *
 * See LICENSE file for details.
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

// Custom device structure definitions
// These structures are dynamically generated based on YAML configuration

// Structure definition for led_strip
typedef struct {
    const char *name;           /*!< Custom device name */
    const char *type;           /*!< Device type: "custom" */
    const char *chip;           /*!< Chip name */
    int8_t       max_leds;
    uint8_t     peripheral_count;
    const char *peripheral_name;
} dev_custom_led_strip_config_t;

// Structure definition for camera
typedef struct {
    const char *name;           /*!< Custom device name */
    const char *type;           /*!< Device type: "custom" */
    const char *chip;           /*!< Chip name */

} dev_custom_camera_config_t;

// Structure definition for audio_dac
typedef struct {
    const char *name;           /*!< Custom device name */
    const char *type;           /*!< Device type: "custom" */
    const char *chip;           /*!< Chip name */
    int16_t      sample_rate_hz;
} dev_custom_audio_dac_config_t;

// Structure definition for audio_adc
typedef struct {
    const char *name;           /*!< Custom device name */
    const char *type;           /*!< Device type: "custom" */
    const char *chip;           /*!< Chip name */
    int16_t      sample_rate_hz;
} dev_custom_audio_adc_config_t;

