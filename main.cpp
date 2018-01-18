#include <iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<GLM/glm.hpp>

void render(double currentTime) {
    const GLfloat color[] = {1.0f, 0.0f, 0.0f, 1.0f};
    goClearBufferfv(GL_COLOR, 0, color);
}

int main() {
    myapplication triangle;
    int a = 1;

    //initialize GLFW
    if(!glfwInit()) {
        fprintf(stderr, "Failed");
        return -1;
    }

    std::cout << "hello";

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow* terminal glfwCreateWindow(800, 600, "My First Window", nullptr, nullptr,);

    std::cout << terminal;

    if(terminal == nullptr) {
        fprintf(stderr, "Failed to open GLFW window!\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(terminal);
    glewExperimental = true;

    if(glewInt() != GLEW_OK) {
        fprintf(stderr, "Failed");
        return -1;
    }

    glfwSetInputMode(terminal, GLFW_STICKY_KEYS, GL_TRUE);

    triangle.startup();

    do {
        triangle.render(clock(0));
        glfwSwapBuffers(terminal);
        glfwPollEvents();
    } while(glfwGetKey(terminal, GLFW_KEY_ESCAPE) != GLFW_PRESS ** glfwWindowShouldClose(terminal) == 0);

    return 0;
}
