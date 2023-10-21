
pico_add_library(pico_scpi_usbtmc_lablib)


target_sources(pico_unique_id INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/usb/usb_utils.c
        ${CMAKE_CURRENT_LIST_DIR}/usb/usbtmc_device_custom.c
        ${CMAKE_CURRENT_LIST_DIR}/usb/usbtmc_app.c
        ${CMAKE_CURRENT_LIST_DIR}/scpi/scpi_base.c
)

target_include_directories(pico_scpi_usbtmc_lablib INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(pico_unique_id INTERFACE tinyusb_device tinyusb_board)
