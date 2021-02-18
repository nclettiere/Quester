cmake_minimum_required(VERSION 3.15)
project(QCore)

set(CMAKE_CXX_STANDARD 17)


# Poco Options
option(ENABLE_FOUNDATION "Enable Foundation, required by all components except CppUnit" ON)
option(ENABLE_ENCODINGS "Enable Encodings" ON)
option(ENABLE_ENCODINGS_COMPILER "Enable Encodings Compiler" OFF)
option(ENABLE_XML "Enable XML" OFF)
option(ENABLE_JSON "Enable JSON" OFF)
option(ENABLE_MONGODB "Enable MongoDB" OFF)
option(ENABLE_DATA_SQLITE "Enable Data SQlite" OFF)
option(ENABLE_REDIS "Enable Redis" OFF)
option(ENABLE_PDF "Enable PDF" OFF)
option(ENABLE_UTIL "Enable Util" ON)
option(ENABLE_NET "Enable Net" OFF)

option(ENABLE_SEVENZIP "Enable SevenZip" OFF)
option(ENABLE_ZIP "Enable Zip" ON)
option(ENABLE_CPPPARSER "Enable C++ parser" OFF)
option(ENABLE_POCODOC "Enable Poco Documentation Generator" OFF)
option(ENABLE_PAGECOMPILER "Enable PageCompiler" OFF)
option(ENABLE_PAGECOMPILER_FILE2PAGE "Enable File2Page" OFF)

file(GLOB QCore_SOURCE
        "src/Core/*.cxx"
        "src/Core/*.cpp"
        "include/Core/*.hpp"
        "include/Core/*.hxx")

set(SOURCES ${QCore_SOURCE})

add_library(QCore STATIC ${SOURCES})

if (CMAKE_GENERATOR MATCHES "Visual Studio")
    SET(RUNTIME_OUTPUT_DIRECTORY "C:/Users/Percebe64/QuesterProjects/ABC")
endif()

add_subdirectory(vendor/poco)
add_subdirectory(vendor/spdlog)

target_link_libraries(QCore PRIVATE d3d11 d3dcompiler dxgi spdlog::spdlog Poco::Foundation Poco::Data Poco::Util Poco::Zip)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(QCore PUBLIC DEBUG=1)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(QCore PUBLIC DEBUG=0)
endif()

target_include_directories(QCore
    PUBLIC
    include/
    src/
    vendor/)