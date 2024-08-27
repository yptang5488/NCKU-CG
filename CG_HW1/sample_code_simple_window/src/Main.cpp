#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include "glm/vec4.hpp"

#include <iostream>
#include <string>

namespace constant
{
const int width{800};
const int height{600};
const std::string name{"SampleCode"};
const glm::vec4 background_color{0.4f, 0.2f, 0.3f, 1.0f};
} // namespace constant

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(constant::width, constant::height,
                                          constant::name.c_str(), NULL, NULL);
    if (!window)
    {
        std::cout << "[Error] Failed to initialize GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "[Error] Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL: " << glGetString(GL_VERSION) << "\n"
              << "Renderer: " << glGetString(GL_RENDERER) << "\n"
              << "Vendor: " << glGetString(GL_VENDOR) << "\n"
              << "Shading Language: "
              << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }


        glClearColor(constant::background_color.x, constant::background_color.y,
                     constant::background_color.z,
                     constant::background_color.a);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
