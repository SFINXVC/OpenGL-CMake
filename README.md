# OpenGL-CMake

OpenGL-CMake is a starter project/template designed to help individuals learn OpenGL without worrying about the complexities of setting up the project. It includes a basic GLFW window with an OpenGL context and a simple shader program that renders a colorful triangle.

## Prerequisites
- CMake (minimum version 3.15)
- Your favorite C++ compiler (i'm using MSVC)

## Getting Started

1. Clone the repository:

   ```bash
   git clone https://github.com/sfinxvc/OpenGL-CMake.git
   cd OpenGL-CMake
   ```

3. Navigate to the project root and create a build directory:

   ```bash
   cd ..
   mkdir build
   cd build
   ```

4. Generate the build system using CMake:

   ```bash
   cmake ..
   ```

5. Build the project:

   ```bash
   cmake --build .
   ```

6. Run the executable:

   ```bash
   ./OpenGL-CMake
   ```

   This should open a GLFW window displaying a colorful triangle rendered using OpenGL.

## Project Structure

- `libs/`: Directory containing external dependencies.
  - `CMakeLists.txt`: CMake configuration file for building dependencies.
  - `glfw/`, `glad/`, `spdlog/`: External dependencies.
- `src/`: Directory containing the main source code.
  - `CMakeLists.txt`: CMake configuration file for the source code.
  - `main.cc`: The main C++ source file containing the OpenGL code.
- `CMakeLists.txt`: The main CMake configuration file for the project.

## Troubleshooting

- If you encounter any issues during setup or building, please refer to the documentation of individual dependencies for troubleshooting tips.

## Credits

- This project uses GLFW, Glad, spdlog, and other open-source libraries.
