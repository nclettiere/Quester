cmake_minimum_required(VERSION 3.10)

#set the project name
project(Quester)

include_directories(${CMAKE_SOURCE_DIR})

# Add all classes in the internal folder
file(GLOB_RECURSE internal_source "src/internal/private/*.cpp" "src/internal/public/*.h")
# Add VENDOR: imgui | imgui-node-editor
file(GLOB imgui_source "vendor/imgui/*.cpp" "vendor/imgui/*.h")
file(GLOB imgui_node_editor_source "vendor/imgui-node-editor/*.cpp" "vendor/imgui-node-editor/*.h")

set(SOURCES src/Quester.cpp src/Quester.h ${internal_source} ${imgui_source} "vendor/imgui/backends/imgui_impl_opengl3.cpp" "vendor/imgui/backends/imgui_impl_opengl3.h" ${imgui_node_editor_source})
add_executable(Quester ${SOURCES})
target_include_directories(Quester PRIVATE "vendor/imgui/")

IF (WIN32)
  set_target_properties(Quester PROPERTIES LINK_FLAGS /SUBSYSTEM:WINDOWS)
ELSE()
  # set stuff for other systems
ENDIF()


# Find POCO and WxWidgets libraries
find_package(wxWidgets REQUIRED COMPONENTS net gl core base)
find_package(OpenGL REQUIRED)
find_package(Poco REQUIRED COMPONENTS Foundation Net JSON)
if(wxWidgets_FOUND)
  include(${wxWidgets_USE_FILE})
  message( "MEp ${GLEW_VERSION}")
  # and for each of your dependent executable/library targets:
endif()

IF (WIN32)
  list(APPEND CMAKE_PREFIX_PATH "C:/Program Files (x86)/glew")
ENDIF()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})

    IF (WIN32)
        include_directories("C:\\Program Files (x86)\\glew\\include")
    ENDIF()
    
    message( "MEp ${GLEW_INCLUDE_DIRS}")
    target_link_libraries(Quester PUBLIC ${wxWidgets_LIBRARIES} ${GLEW_LIBRARIES} GLEW::GLEW opengl32 Poco::Foundation Poco::Net Poco::JSON)
endif()

file(GLOB Public_Files
  "Public/*"
)
file(COPY ${Public_Files} DESTINATION ${CMAKE_BINARY_DIR}/Public/)
