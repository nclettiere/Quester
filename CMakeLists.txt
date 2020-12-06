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

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

find_package(Poco REQUIRED Foundation Data DataSQLite JSON)
if(Poco_FOUND)
  message( "Poco Found ${Poco_Version}")
else()
    message("Poco not found.")
endif()

qt5_add_resources(DarkTheme_Resource
    "vendor/Qt-Frameless-Window-DarkStyle/darkstyle.qrc"
    "vendor/Qt-Frameless-Window-DarkStyle/framelesswindow.qrc")

file(GLOB_RECURSE internal_source
    "src/internal/private/*.cpp"
    "src/internal/public/*.hpp"
    "src/internal/public/*.h"
    "src/internal/private/*.ui"
    "src/internal/private/*.qml")

file(GLOB_RECURSE dark_theme
    "vendor/Qt-Frameless-Window-DarkStyle/DarkStyle.cpp"
    "vendor/Qt-Frameless-Window-DarkStyle/DarkStyle.h"
    "vendor/Qt-Frameless-Window-DarkStyle/framelesswindow/*.h"
    "vendor/Qt-Frameless-Window-DarkStyle/framelesswindow/*.cpp"
    "vendor/Qt-Frameless-Window-DarkStyle/framelesswindow/*.ui")

set(SOURCES src/main.cpp ${internal_source} ${dark_theme})
add_executable(Quester ${SOURCES} ${DarkTheme_Resource})
target_link_libraries(Quester PRIVATE Qt${QT_VERSION_MAJOR}::Widgets nodes Poco::Foundation Poco::Data Poco::DataSQLite Poco::JSON)

file(GLOB Public_Files "Public/*")
file(COPY ${Public_Files} DESTINATION ${CMAKE_BINARY_DIR}/Public/)
