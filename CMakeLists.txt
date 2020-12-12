cmake_minimum_required(VERSION 3.5)

project(Quester)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory("vendor/nodeeditor")
include_directories(
    "src/internal"
    "vendor/poco/Foundation/include"
    "vendor/poco/Data/include"
    "vendor/poco/Foundation/include"
    "vendor/poco/JSON/include"
    "vendor/poco/Data/SQLite/include"
    "vendor/Qt-Frameless-Window-DarkStyle/")

find_package(QT NAMES Qt5 COMPONENTS Widgets Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Sql REQUIRED)

find_package(Poco REQUIRED Foundation Data DataSQLite JSON)
if(Poco_FOUND)
  message( "Poco Found ${Poco_Version}")
else()
    message("Poco not found.")
endif()

file(GLOB_RECURSE internal_source
    "src/internal/private/*.cpp"
    "src/internal/public/*.hpp"
    "src/internal/public/*.h"
    "src/internal/private/*.ui"
    "src/internal/private/*.qml")

set(SOURCES src/main.cpp ${internal_source})
add_executable(Quester ${SOURCES})
target_link_libraries(Quester PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql nodes Poco::Foundation Poco::Data Poco::DataSQLite Poco::JSON)

file(GLOB Public_Files "Public/*")
file(COPY ${Public_Files} DESTINATION ${CMAKE_BINARY_DIR}/Public/)
