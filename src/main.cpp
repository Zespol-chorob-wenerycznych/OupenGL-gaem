#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

auto static const program = []() noexcept -> int
{
    #pragma region Glfw initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto window = glfwCreateWindow(1280, 720, "gaem", nullptr, nullptr);

    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    #pragma endregion
    #pragma region Glad initialization
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return EXIT_FAILURE;
    }
    #pragma endregion

    int w, h;
    glfwGetWindowSize(window, &w, &h);
    glViewport(0, 0, w, h);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);  

    while(!glfwWindowShouldClose(window))
    {
        #pragma region Fps counter
        static double previousTime = glfwGetTime();
        static unsigned frameCount = 0;
        double currentTime = glfwGetTime();
        ++frameCount;

        if (currentTime - previousTime >= 1.0)
        {
            glfwSetWindowTitle(window, (std::string("Frames per second: ") + std::to_string(frameCount)).c_str());

            frameCount = 0;
            previousTime = currentTime;
        }
        #pragma endregion

        processInput(window);

        #pragma region Render commands
        glClearColor(1.f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        #pragma endregion

        glfwSwapBuffers(window);
        glfwPollEvents();         
    }

    #pragma region Termination
    glfwDestroyWindow(window);
    glfwTerminate();
    #pragma endregion
    return 0;
};

auto main() -> int
{
    return program();
}