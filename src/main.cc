#include <cstring>
#include <cstdint>
#include <cstdio>

#include <memory>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

auto framebuff_size_callback(GLFWwindow* window, int width, int height) -> void
{
    glViewport(0, 0, width, height);
}

auto process_input(GLFWwindow* window) -> void
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

#define _tmain main
auto _tmain(int argc, char const* argv[]) -> int
{
    std::shared_ptr<spdlog::logger> console = spdlog::stdout_color_mt("console");

    if (!console)
        throw std::runtime_error("unlogical shit");

    spdlog::set_pattern("[%H:%M:%S %z] [%^%l%$] [%s:%#] %v");

    SPDLOG_INFO("initializing glfw, please wait...");

    if (glfwInit() != GLFW_TRUE)
        SPDLOG_ERROR("failed to initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // initialize a new window (for mikocok wingdos)
    GLFWwindow* window = glfwCreateWindow(800, 600, "cpp-game", NULL, NULL);
    if (!window)
    {
        SPDLOG_ERROR("failed to create a GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuff_size_callback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        SPDLOG_ERROR("failed to initialize GLAD");
        return -1;
    }

    IMGUI_CHECKVERSION();

    // Limit FPS (vsync)
    glfwSwapInterval(1);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // Verter Buffer Obj (VBO) and Vertex Array Obj (VAO) setup
    std::uint32_t vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    // Bind VAO
    glBindVertexArray(vao);

    // Bind VBO and set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Vertex shader source
    const char* vertex_shader_source = R"( 
        #version 150 core
        in vec3 aPos;
        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )";

    // Fragment shader setup
    const char* fragment_shader_source = R"(
        #version 150 core
        out vec4 FragColor;
        void main()
        {
            // Calculate a gradient based on the fragment's Y-coordinate
            float gradient = gl_FragCoord.y / 600.0; // Adjust 600.0 based on your window size

            // Map the gradient to the rainbow colors
            vec3 rainbowColor = vec3(1.0 - gradient, gradient, 0.0);

            // Set the final color
            FragColor = vec4(rainbowColor, 1.0);
        }
    )";

    std::uint32_t vertex_shader, fragment_shader, shader_program;

    // Vertex shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    // Check for shader compile errors
    int success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        SPDLOG_ERROR("Vertex shader compilation failed: {}", info_log);
    }

    // Fragment shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);

    // Check for shader compile errors
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        SPDLOG_ERROR("Fragment shader compilation failed: {}", info_log);
    }

    // Shader program
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    // Check for shader program linking errors
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        SPDLOG_ERROR("Shader program linking failed: {}", info_log);
    }

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    while (!glfwWindowShouldClose(window))
    {
        process_input(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program and draw the triangle
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
