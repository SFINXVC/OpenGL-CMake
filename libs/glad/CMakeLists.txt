cmake_minimum_required(VERSION 3.15)

project(glad)

add_library(glad include/glad/glad.h src/glad.c)
target_include_directories(${PROJECT_NAME} PUBLIC include/)