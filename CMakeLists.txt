cmake_minimum_required(VERSION 3.21..3.31)
if(CMAKE_HOST_APPLE AND NOT DEFINED CMAKE_OSX_DEPLOYMENT_TARGET
   AND (NOT DEFINED CMAKE_SYSTEM_NAME OR CMAKE_SYSTEM_NAME STREQUAL "Darwin"))
    set(CMAKE_OSX_DEPLOYMENT_TARGET "15.0" CACHE STRING "Minimum supported macOS version")
endif()
project(parasite-eve-ii-pc VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# PsyZ: our fork of the PsyZ PSY-Q replacement (SDL3 video/audio/input, libgte, libcd, MDEC).
set(PSYZ_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/psyz)
add_subdirectory(${PSYZ_DIR}/psyz ${CMAKE_CURRENT_BINARY_DIR}/psyz)
target_compile_definitions(psyz PRIVATE __psyz)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    # The original task/actor workspaces are accessed through several layout views.
    add_compile_options("$<$<COMPILE_LANGUAGE:C>:-fno-strict-aliasing>"
        "$<$<COMPILE_LANGUAGE:C>:-ffunction-sections>"
        "$<$<COMPILE_LANGUAGE:C>:-fdata-sections>")
endif()

# The game proper (the former decompilation sources), compiled for the host.
file(GLOB GAME_MAIN_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/main/*.c)
add_library(game_main OBJECT ${GAME_MAIN_SOURCES})
target_include_directories(game_main PUBLIC include include/decomp
    ${CMAKE_CURRENT_SOURCE_DIR}/build/include)
target_compile_definitions(game_main PUBLIC __psyz SKIP_ASM)
target_compile_options(game_main PRIVATE -w)
target_link_libraries(game_main PUBLIC psyz)

add_executable(parasite-eve-ii-pc src/port/main.c $<TARGET_OBJECTS:game_main>)
target_include_directories(parasite-eve-ii-pc PRIVATE include)
target_compile_definitions(parasite-eve-ii-pc PRIVATE __psyz)
target_link_libraries(parasite-eve-ii-pc PRIVATE psyz)
