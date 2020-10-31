cmake_minimum_required(VERSION 3.10)

#set the project name
project(Quester)

include_directories(${CMAKE_SOURCE_DIR})

# Add all classes in the internal folder
file(GLOB_RECURSE source_list "src/internal/private/*.cpp" "src/internal/public/*.h")

add_executable(Quester src/App.cpp ${source_list})

IF (WIN32)
  set_target_properties(Quester PROPERTIES LINK_FLAGS /SUBSYSTEM:WINDOWS)
ELSE()
  # set stuff for other systems
ENDIF()


# Find POCO and WxWidgets libraries
find_package(wxWidgets REQUIRED COMPONENTS net gl core base png tiff jpeg zlib regex expat)
find_package(Poco REQUIRED COMPONENTS Foundation Net JSON)
if(wxWidgets_FOUND)
  include(${wxWidgets_USE_FILE})
  # and for each of your dependent executable/library targets:
  target_link_libraries(Quester PUBLIC ${wxWidgets_LIBRARIES} Poco::Foundation Poco::Net Poco::JSON)
endif()
