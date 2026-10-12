#!/usr/bin/env python3
import os
import sys

def patch_file(path, old, new):
    if not os.path.exists(path):
        return
    with open(path, "r", encoding="utf-8") as f:
        content = f.read()
    if new in content:
        return
    if old in content:
        content = content.replace(old, new)
        with open(path, "w", encoding="utf-8") as f:
            f.write(content)
        print(f"[patch_managed_components] Patched {path}")

def main():
    base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    bmgr_dir = os.path.join(base_dir, "managed_components", "espressif__esp_board_manager")
    if not os.path.isdir(bmgr_dir):
        return

    # 1. Patch periph_ledc.h for IDF 5.3 ESP32-S3 sleep retention compatibility
    ledc_h = os.path.join(bmgr_dir, "peripherals", "periph_ledc", "periph_ledc.h")
    old_ledc = '#include "driver/ledc.h"\n'
    new_ledc = '''#include "driver/ledc.h"

#ifndef SOC_LEDC_SUPPORT_SLEEP_RETENTION
typedef int ledc_sleep_mode_t;
#define LEDC_SLEEP_MODE_NO_ALIVE_NO_PD 0
#define LEDC_SLEEP_MODE_KEEP_ALIVE 1
#define LEDC_SLEEP_MODE_NO_ALIVE_ALLOW_PD 2
#endif
'''
    patch_file(ledc_h, old_ledc, new_ledc)

    # 2. Patch periph_spi.py to only set data_io_default_level on IDF >= 5.4
    spi_py = os.path.join(bmgr_dir, "peripherals", "periph_spi", "periph_spi.py")
    if os.path.exists(spi_py):
        with open(spi_py, "r", encoding="utf-8") as f:
            content = f.read()
        if "'data_io_default_level': data_io_default_level" in content:
            content = content.replace(
                "            'data_io_default_level': data_io_default_level,\n",
                ""
            )
            content = content.replace(
                "        if get_idf_version() >= IDF_VERSION_WITH_SPI_DMA_BURST_SIZE:",
                "        if get_idf_version() >= (5, 4, 0):\n            spi_bus_config_init['data_io_default_level'] = data_io_default_level\n        if get_idf_version() >= IDF_VERSION_WITH_SPI_DMA_BURST_SIZE:"
            )
            with open(spi_py, "w", encoding="utf-8") as f:
                f.write(content)
            print(f"[patch_managed_components] Patched {spi_py}")

    # 3. Patch periph_rmt.py for IDF 5.3 compatibility
    rmt_py = os.path.join(bmgr_dir, "peripherals", "periph_rmt", "idf5", "periph_rmt.py")
    if os.path.exists(rmt_py):
        with open(rmt_py, "r", encoding="utf-8") as f:
            content = f.read()
        if "'allow_pd': bool(tx_cfg.get('flags', {}).get('allow_pd', False))," in content:
            content = content.replace(
                "from generators.utils.logger import get_logger\n",
                "from generators.utils.logger import get_logger\nfrom generators.utils.idf_version import get_idf_version\n"
            )
            content = content.replace(
                "                'allow_pd': bool(tx_cfg.get('flags', {}).get('allow_pd', False)),\n                'init_level': int(tx_cfg.get('flags', {}).get('init_level', 0)),\n",
                ""
            )
            content = content.replace(
                "        channel_config = {'tx': tx_config}",
                "        if get_idf_version() >= (5, 4, 0):\n            tx_config['flags']['allow_pd'] = bool(tx_cfg.get('flags', {}).get('allow_pd', False))\n            tx_config['flags']['init_level'] = int(tx_cfg.get('flags', {}).get('init_level', 0))\n        channel_config = {'tx': tx_config}"
            )
            content = content.replace(
                "                'allow_pd': bool(rx_cfg.get('flags', {}).get('allow_pd', False)),\n",
                ""
            )
            content = content.replace(
                "        channel_config = {'rx': rx_config}",
                "        if get_idf_version() >= (5, 4, 0):\n            rx_config['flags']['allow_pd'] = bool(rx_cfg.get('flags', {}).get('allow_pd', False))\n        channel_config = {'rx': rx_config}"
            )
            with open(rmt_py, "w", encoding="utf-8") as f:
                f.write(content)
            print(f"[patch_managed_components] Patched {rmt_py}")

if __name__ == "__main__":
    main()
