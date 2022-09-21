#ifndef SPACE_WINDOW_HPP
#define SPACE_WINDOW_HPP

#include <string>
#include <iostream>

#include<glad/glad.h>
#include <GLFW/glfw3.h>

struct WindowData {
    std::string title;
    int width;
    int height;
};

class Window {
public:
    Window(const std::string &title, int width, int height);

    ~Window();

    GLFWwindow *get_native_window() { return nativeWindow; }

    int getWidth() const { return data.width; }

    int getHeight() const { return data.height; }

    std::string getTitle() const { return data.title; }

    void update();

private:
    WindowData data;
    GLFWwindow *nativeWindow;

    void updateSize(int width, int height);
};

#endif // SPACE_WINDOW_HPP
