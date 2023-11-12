
pico_add_library(pico_scpi_usbtmc_lablib)


target_sources(pico_unique_id INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/usb/usb_utils.c
        ${CMAKE_CURRENT_LIST_DIR}/usb/usbtmc_device_custom.c
        ${CMAKE_CURRENT_LIST_DIR}/usb/usb_descriptors_common.c
        ${CMAKE_CURRENT_LIST_DIR}/usb/usbtmc_app.c
        ${CMAKE_CURRENT_LIST_DIR}/scpi/scpi_base.c
        ${CMAKE_CURRENT_LIST_DIR}/scpi-parser/libscpi/src/parser.c
        ${CMAKE_CURRENT_LIST_DIR}/scpi-parser/libscpi/src/lexer.c
        ${CMAKE_CURRENT_LIST_DIR}/scpi-parser/libscpi/src/error.c
        ${CMAKE_CURRENT_LIST_DIR}/scpi-parser/libscpi/src/ieee488.c
        ${CMAKE_CURRENT_LIST_DIR}/scpi-parser/libscpi/src/minimal.c
        ${CMAKE_CURRENT_LIST_DIR}/scpi-parser/libscpi/src/utils.c
        ${CMAKE_CURRENT_LIST_DIR}/scpi-parser/libscpi/src/units.c
        ${CMAKE_CURRENT_LIST_DIR}/scpi-parser/libscpi/src/fifo.c
)

target_include_directories(pico_scpi_usbtmc_lablib INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/scpi-parser/libscpi/inc

)

target_link_libraries(pico_scpi_usbtmc_lablib INTERFACE tinyusb_device tinyusb_board)
