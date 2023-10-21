cmake_minimum_required(VERSION 3.13)

# set(PICO_DEOPTIMIZED_DEBUG 1)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_scpi_usbtmc_lablib C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "  Diag: maximum debug info")
    #I've set this to allow breakpoints on any source line
    set(PICO_DEOPTIMIZED_DEBUG=1)
endif ()

pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function 
        -Wno-maybe-uninitialized
        )


# enable use of scpi_user_config.h, to support custom device specific registers 
target_compile_definitions(pico_scpi_usbtmc_lablib PRIVATE SCPI_USER_CONFIG=1)

# usb output, uart output
 pico_enable_stdio_usb(pico_scpi_usbtmc_lablib 0)
 pico_enable_stdio_uart(pico_scpi_usbtmc_lablib 0)
