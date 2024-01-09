cmake_minimum_required(VERSION 3.15)

add_definitions(-D__CMAKE_ROOT_DIRECTORY__="${CMAKE_CURRENT_SOURCE_DIR}/..")

find_package(Threads REQUIRED)

file(GLOB SOURCE_FILES
	*.cc
	**/*.cc
	**/**/*.cc
	**/**/**/*.cc
)

file(GLOB HEADER_FILES
	*.hh
	**/*.hh
	**/**/*.hh
	**/**/**/*.hh
)

add_executable(${PROJECT_NAME}
	${SOURCE_FILES}
	${HEADER_FILES}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
	spdlog imgui glad fmt glm glfw magic_enum ${CMAKE_THREAD_LIBS_INIT}
)

target_include_directories(${PROJECT_NAME} PRIVATE .)