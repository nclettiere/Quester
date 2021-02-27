cmake_minimum_required(VERSION 3.15)

project(QEditor VERSION 1.0.0 DESCRIPTION "Handles the editor windows and its contents. Works in conjuction of QGraphics library.")

set(CMAKE_CXX_STANDARD 17)
set(imgui_DIR ${CMAKE_CURRENT_LIST_DIR}/../../vendor/imgui/)

file(GLOB imgui_SOURCE
        "${imgui_DIR}/*.cpp"
        "${imgui_DIR}/*.h")

file(GLOB QEditor_SOURCE
        "src/Editor/*.cxx"
        "src/Editor/*.cpp"
        "include/Editor/*.h[xx/pp]")

set(SOURCES ${QEditor_SOURCE})

add_library(QEditor SHARED ${SOURCES})
set_target_properties(QEditor PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../.." )
set_target_properties(QEditor PROPERTIES LIBRARY_OUTPUT_DIRECTORY "../.." )
set_target_properties(QEditor PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(QEditor PROPERTIES SOVERSION 1)

target_link_libraries(QEditor QGraphics)

target_include_directories(QEditor
        PUBLIC
        include/
        src/
        ${imgui_DIR}
        ../Core/include
        ../Graphics/include)