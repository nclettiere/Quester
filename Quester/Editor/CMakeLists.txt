cmake_minimum_required(VERSION 3.15)
project(QEditor)

set(CMAKE_CXX_STANDARD 17)
set(imgui_VERSION 1.81)
set(imgui_DIR ${CMAKE_CURRENT_LIST_DIR}/../../vendor/imgui-${imgui_VERSION}/)

file(GLOB imgui_SOURCE
        "${imgui_DIR}/*.cpp"
        "${imgui_DIR}/*.h")

file(GLOB QEditor_SOURCE
        "src/Editor/*.cxx"
        "src/Editor/*.cpp"
        "include/Editor/*.h[xx/pp]")

set(SOURCES ${QEditor_SOURCE})

add_library(QEditor STATIC ${SOURCES})

target_link_libraries(QEditor QGraphics)

target_include_directories(QEditor
        PUBLIC
        include/
        src/
        ${imgui_DIR}
        ../Core/include
        ../Graphics/include)