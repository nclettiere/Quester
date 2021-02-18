cmake_minimum_required(VERSION 3.15)
project(Quester)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE Quester_SOURCE
        "src/*.cxx"
        "src/*.cpp"
        "src/Windows/*.cpp"
        "src/Windows/*.cxx"
        "include/*.h[pp]")

set(SOURCES src/main.cxx ${Quester_SOURCE} src/Windows/ProjectSelectorWindow.cpp)

add_executable(Quester ${SOURCES})

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(Quester PUBLIC DEBUG=1)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(Quester PUBLIC DEBUG=0)
endif()

add_subdirectory(Quester/Core)
add_subdirectory(Quester/Graphics)
add_subdirectory(Quester/Editor)

#set_target_properties(Quester PROPERTIES
#        LINK_FLAGS /SUBSYSTEM:CONSOLE)


target_link_libraries(Quester PRIVATE QCore QGraphics QEditor)

target_include_directories(Quester PRIVATE
        include/
        src/
        Quester/Core/include
        Quester/Graphics/include
        Quester/Editor/include)