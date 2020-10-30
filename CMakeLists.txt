cmake_minimum_required(VERSION 3.10)

#set the project name
project(Quester)

add_executable(Quester src/main.cpp)

# Note that for MinGW users the order of libs is important!
find_package(wxWidgets COMPONENTS net gl core base)
if(wxWidgets_FOUND)
  include(${wxWidgets_USE_FILE})
  # and for each of your dependent executable/library targets:
  target_link_libraries(Quester ${wxWidgets_LIBRARIES})
endif()