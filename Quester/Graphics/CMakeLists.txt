cmake_minimum_required(VERSION 3.15)
project(QGraphics CXX)

set(CMAKE_CXX_STANDARD 17)
set(SDL2_VERSION 2.0.14)

set(SDL2_INCLUDE_DIRS "../../vendor/SDL2-${SDL2_VERSION}/include/")
# Support both 32 and 64 bit builds
if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/../../vendor/SDL2-${SDL2_VERSION}/lib/x64/SDL2main.lib;${CMAKE_CURRENT_LIST_DIR}/../../vendor/SDL2-${SDL2_VERSION}/lib/x64/SDL2.lib")
    set(SDL2_DLL "${CMAKE_CURRENT_LIST_DIR}/../../vendor/SDL2-${SDL2_VERSION}/lib/x64/SDL2.dll")
    message(STATUS "-> USING SDL x64")
else ()
    set(SDL2_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/../../vendor/SDL2-${SDL2_VERSION}/lib/x86/SDL2main.lib;${CMAKE_CURRENT_LIST_DIR}/../../vendor/SDL2-${SDL2_VERSION}/lib/x86/SDL2.lib")
    set(SDL2_DLL "${CMAKE_CURRENT_LIST_DIR}/../../vendor/SDL2-${SDL2_VERSION}/lib/x86/SDL2.dll")
    message(STATUS "-> USING SDL x86")
endif ()
string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

set(imgui_DIR ${CMAKE_CURRENT_LIST_DIR}/../../vendor/imgui/)

file(GLOB SDL2_SOURCE
        "${SDL2_INCLUDE_DIRS}/*.h")

file(GLOB QGraphics_SOURCE
        "src/Graphics/*.cxx"
        "src/Graphics/*.cpp"
        "include/Graphics/*.h[pp/xx]")

file(GLOB imgui_SOURCE
        "${imgui_DIR}/*.cpp"
        "${imgui_DIR}/*.h"
        "${imgui_DIR}/misc/cpp/*.cpp"
        "${imgui_DIR}/misc/cpp/*.h"
        "${imgui_DIR}/backends/imgui_impl_dx11.cpp"
        "${imgui_DIR}/backends/imgui_impl_dx11.h"
        "${imgui_DIR}/backends/imgui_impl_sdl.cpp"
        "${imgui_DIR}/backends/imgui_impl_sdl.h")

set(SOURCES ${QGraphics_SOURCE} ${SDL2_SOURCE} ${imgui_SOURCE})

add_library(QGraphics STATIC ${SOURCES})

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(QGraphics PUBLIC DEBUG=1)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(QGraphics PUBLIC DEBUG=0)
endif()

target_link_libraries(QGraphics ${SDL2_LIBRARIES})

target_include_directories(QGraphics
    PUBLIC
    include/
    src/
    ${SDL2_INCLUDE_DIRS}
    ${imgui_DIR}/
    ${imgui_DIR}/backends/
    ../Core/include/)

file(GLOB FONTS "${CMAKE_CURRENT_LIST_DIR}/../../vendor/fonts/*")
file(GLOB TEXTURES "${CMAKE_CURRENT_LIST_DIR}/../../vendor/textures/*")

file(COPY ${SDL2_DLL} DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY ${FONTS} DESTINATION ${CMAKE_BINARY_DIR}/assets/fonts/)
file(COPY ${TEXTURES} DESTINATION ${CMAKE_BINARY_DIR}/assets/textures/)