cmake_minimum_required(VERSION 3.15)

project(imgui)

file(GLOB IMGUI_SOURCES
  imgui.cpp
  imgui_demo.cpp
  imgui_draw.cpp
  imgui_widgets.cpp
)

file(GLOB IMGUI_HEADERS
  imgui.h
  backends/imgui_impl_glfw.h
  backends/imgui_impl_opengl3.h
)

add_library(${PROJECT_NAME} STATIC ${IMGUI_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC . backends/)
