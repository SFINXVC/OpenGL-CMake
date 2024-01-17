cmake_minimum_required(VERSION 3.15)

add_definitions(-D__CMAKE_ROOT_DIRECTORY__="${CMAKE_CURRENT_SOURCE_DIR}/..")

file(GLOB SOURCE_FILES
	main.cc
)

add_executable(${PROJECT_NAME}
	${SOURCE_FILES}
)

set(CMAKE_CONFIGURATION_TYPES Release CACHE STRING INTERNAL FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

target_link_libraries(${PROJECT_NAME} PUBLIC
	spdlog glad glfw
)

target_include_directories(${PROJECT_NAME} PRIVATE .)