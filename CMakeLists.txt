cmake_minimum_required(VERSION 3.10)

#set the project name
project(Quester)

include_directories(${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE source_list "src/internal/private/*.cpp")

add_executable(Quester src/App.cpp ${source_list})

# Note that for MinGW users the order of libs is important!
find_package(wxWidgets COMPONENTS net gl core base)
if(wxWidgets_FOUND)
  include(${wxWidgets_USE_FILE})
  # and for each of your dependent executable/library targets:
  target_link_libraries(Quester ${wxWidgets_LIBRARIES})
endif()