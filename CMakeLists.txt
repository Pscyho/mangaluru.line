# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_FETCH_FROM_GIT on)
# set(PICO_SDK_PATH "/nix/store/j547v5jm9hd709gh001jvjbc2adcm933-pico-sdk-2.0.0/lib/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(pico-on-line C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
file(GLOB ALL_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        )
add_executable(pico-on-line 
${ALL_SRCS} )

pico_set_program_name(pico-on-line "pico-on-line")
pico_set_program_version(pico-on-line "0.1")

pico_enable_stdio_uart(pico-on-line 1)
pico_enable_stdio_usb(pico-on-line 1)

# Add the standard library to the build
target_link_libraries(pico-on-line
        pico_stdlib
        hardware_pwm)

# Add the standard include files to the build
target_include_directories(pico-on-line PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${CMAKE_CURRENT_LIST_DIR}/src # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
target_link_libraries(pico-on-line 
        )

pico_add_extra_outputs(pico-on-line)

