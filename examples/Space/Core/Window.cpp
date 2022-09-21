#include "Window.hpp"

#include <iostream>

Window::Window(const std::string &title, int width, int height) : data({title, width, height}) {
    int glfwStatus = glfwInit();

    if (!glfwStatus) {
        std::cout << "Couldn't initialize GLFW!\n";
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    nativeWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!nativeWindow) {
        std::cout << "Couldn't initialize GLAD!\n";
    }

    glfwSetWindowUserPointer(nativeWindow, this);

    glfwMakeContextCurrent(nativeWindow);

    int gladStatus = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    if (!gladStatus) {
        std::cout << "Couldn't initialize GLAD!\n";
    }

    std::cout << glfwGetVersionString() << std::endl;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSetFramebufferSizeCallback(nativeWindow, [](GLFWwindow *glfw_window, int width, int height) {
        auto *window = (Window *) glfwGetWindowUserPointer(glfw_window);
        window->updateSize(width, height);
    });

    glfwSetWindowCloseCallback(nativeWindow, [](GLFWwindow *glfw_window) {
        glfwSetWindowShouldClose(glfw_window, 1);
    });

    glfwSetWindowSizeCallback(nativeWindow, [](GLFWwindow* glfw_window, int width, int height){
        auto *window = (Window *) glfwGetWindowUserPointer(glfw_window);
        window->updateSize(width, height);
    });
}

Window::~Window() {
    glfwDestroyWindow(nativeWindow);
    glfwTerminate();
}

void Window::update() {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwPollEvents();
}

void Window::updateSize(int width, int height) {
    data.width = width;
    data.height = height;

    glViewport(0, 0, width, height);
}

