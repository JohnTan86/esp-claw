# Board information output
message(STATUS "Selected Board: esp32_S3_DevKitC_1_breadboard")
message(STATUS "Board Path: /workspace/application/edge_agent/boards/espressif/esp32_S3_DevKitC_1_breadboard")

idf_component_register(
    SRC_DIRS "." "../../boards/espressif/esp32_S3_DevKitC_1_breadboard"
    INCLUDE_DIRS "." "../../boards/espressif/esp32_S3_DevKitC_1_breadboard"
    REQUIRES esp_board_manager
)

# This is equivalent to adding WHOLE_ARCHIVE option to the idf_component_register call above:
idf_component_set_property(${COMPONENT_NAME} WHOLE_ARCHIVE TRUE)
