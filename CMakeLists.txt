cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_BOARD pico_w CACHE STRING "Board type")

include(pico_sdk_import.cmake)

project(ADC_U4C8 CXX ASM)

pico_sdk_init()

add_executable(ADC_U4C8 source.c inc/ssd1306.c)

target_link_libraries(ADC_U4C8 
	pico_stdlib 
	hardware_pwm 
	hardware_adc
)

# Habilitar saída USB (opcional)
pico_enable_stdio_usb(ADC_U4C8 1)
pico_enable_stdio_uart(ADC_U4C8 0)

pico_add_extra_outputs(ADC_U4C8)

# Add executable. Default name is the project name, version 0.1
pico_set_program_name(ADC_U4C8 "ADC_U4C8")
pico_set_program_version(ADC_U4C8 "0.1")

# Add the standard include files to the build
target_include_directories(ADC_U4C8 PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Add any user requested libraries
target_link_libraries(ADC_U4C8)

