idf_component_register(
    SRCS "src/board_esp32_s3_expboard.c"
    INCLUDE_DIRS "include"
    REQUIRES esp_lcd esp32-camera spi_flash
)
