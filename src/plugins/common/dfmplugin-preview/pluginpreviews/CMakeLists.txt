cmake_minimum_required(VERSION 3.10)

set(GlobalFiles ${CMAKE_CURRENT_SOURCE_DIR}/preview_plugin_global.h)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(image-preview)
add_subdirectory(music-preview)
add_subdirectory(pdf-preview)
add_subdirectory(text-preview)
add_subdirectory(dciicon-preview)
if ((NOT ${CMAKE_SYSTEM_PROCESSOR} STREQUAL "sw_64")
        AND (NOT ${CMAKE_SYSTEM_PROCESSOR} STREQUAL "mips64")
        AND (NOT ${CMAKE_SYSTEM_PROCESSOR} STREQUAL "mips32")
        AND (NOT ${CMAKE_SYSTEM_PROCESSOR} STREQUAL "loongarch64")
        AND (NOT ${CMAKE_SYSTEM_PROCESSOR} STREQUAL "riscv64"))
    add_subdirectory(video-preview)
endif()
