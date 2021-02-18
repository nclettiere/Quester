cmake_minimum_required(VERSION 3.15)
project(QCore)

set(CMAKE_CXX_STANDARD 17)

file(GLOB QCore_SOURCE
        "src/Core/*.cxx"
        "src/Core/*.cpp"
        "include/Core/*.hpp"
        "include/Core/*.hxx")

set(SOURCES ${QCore_SOURCE})

add_library(QCore STATIC ${SOURCES})

target_link_libraries(QCore d3d11 d3dcompiler dxgi)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(QCore PUBLIC DEBUG=1)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(QCore PUBLIC DEBUG=0)
endif()

target_include_directories(QCore
    PUBLIC
    include/
    src/)