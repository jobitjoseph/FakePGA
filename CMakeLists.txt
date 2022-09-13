cmake_minimum_required(VERSION 3.12)

add_custom_target(
    verilatorOutput
    COMMAND verilator -cc ${CMAKE_CURRENT_SOURCE_DIR}/verilog/top.v -Wno-INITIALDLY -Wno-UNOPTFLAT -I${CMAKE_CURRENT_SOURCE_DIR}/verilog --top-module top
)

include(pico_sdk_import.cmake)
project(FakePGA)
set(target_name FakePGA)

set(libVerilator "/usr/share/verilator/include")

pico_sdk_init()

add_executable(${target_name})

include_directories(${libVerilator})
include_directories(${CMAKE_CURRENT_BINARY_DIR}/obj_dir)

target_sources(${target_name} PRIVATE
    src/main.cpp
    src/io.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/obj_dir/Vtop.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/obj_dir/Vtop__Syms.cpp
    ${libVerilator}/verilated.cpp
    )

target_link_libraries(${target_name} PRIVATE
    pico_stdlib
    )

add_dependencies(${target_name} verilatorOutput)

# enable usb output, disable uart output
pico_enable_stdio_usb(${target_name} 0)
pico_enable_stdio_uart(${target_name} 0)

pico_add_extra_outputs(${target_name})
