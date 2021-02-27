cmake_minimum_required(VERSION 3.15)

project(QCore VERSION 1.0.0 DESCRIPTION "Under-Layer library of Quester. It handles low level OpenGL and D3D and management of windows, file system and OS related code.")

set(CMAKE_CXX_STANDARD 17)


file(GLOB QCore_SOURCE
        "src/Core/*.cxx"
        "src/Core/*.cpp"
        "include/Core/*.hpp"
        "include/Core/*.hxx")

set(SOURCES ${QCore_SOURCE})

add_library(QCore SHARED ${SOURCES})
set_target_properties(QCore PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(QCore PROPERTIES SOVERSION 1)

add_subdirectory(vendor/spdlog)

set(Poco_DIR C:\\msys64\\mingw64\\bin)
find_package(Poco REQUIRED Foundation Util Data)
if(${Poco_FOUND})
    message(STATUS "Poco Library path found!")
    if(NOT ${Poco_Foundation_FOUND})
        message(FATAL_ERROR "Error: Poco library path is found, but it appears that the Poco::Foundation is missing. Please check your installation.")
    endif()
else()
    message(FATAL_ERROR "Could not find Poco C++ Libraries. Should be installed on the system.")
endif()

find_package(Boost REQUIRED Serialization)
if(${Boost_FOUND})
    message(STATUS "Boost Library path found!")
    if(NOT ${Boost_Serialization_FOUND})
        message(FATAL_ERROR "Error: Boost library path is found, but it appears that the Boost::Serialization is missing. Please check your installation.")
    endif()
else()
    message(FATAL_ERROR "Could not find Boost C++ Libraries. Should be installed on the system.")
endif()

target_link_libraries(QCore PUBLIC d3d11 d3dcompiler dxgi spdlog::spdlog ${Poco_LIBRARIES} ${Boost_LIBRARIES})

if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(QCore PUBLIC DEBUG=1)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_definitions(QCore PUBLIC DEBUG=0)
endif()

target_include_directories(QCore
    PUBLIC
    include/
    src/
    vendor/
    C:\\msys64\\mingw64\\include)
