cmake_minimum_required(VERSION 3.5)

project(Quester)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD_LIBRARIES -lPocoDataSQLite)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# C++ Poco Library (must be installed)
find_package(Poco REQUIRED COMPONENTS Foundation Data Net JSON)
if(Poco_FOUND)
    message( "${Poco_LIBRARIES}" )
else()
    message( "Error => Poco: NOT FOUND")
endif()
# Add all classes in the internal folder
file(GLOB_RECURSE internal_source "src/internal/private/*.cpp" "src/internal/public/*.hpp" "src/internal/public/*.h" "src/internal/private/*.ui" "src/internal/private/*.qml")
set(SOURCES src/main.cpp ${internal_source})

if(ANDROID)
  add_library(Quester SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )
else()
  add_executable(Quester
    ${SOURCES}
  )
endif()

add_subdirectory("vendor/nodeeditor")
target_link_libraries(Quester PRIVATE Qt${QT_VERSION_MAJOR}::Widgets nodes ${Poco_LIBRARIES})
include_directories("src/internal")

file(GLOB Public_Files "Public/*")
file(COPY ${Public_Files} DESTINATION ${CMAKE_BINARY_DIR}/Public/)
