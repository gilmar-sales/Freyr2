#pragma once

#include <iostream>
#include <string>

#include <SDL3/SDL.h>
#include <glad/glad.h>

struct WindowData
{
    std::string title;
    int width;
    int height;
};

class Window
{
  public:
    Window(const std::string &title, int width, int height);

    ~Window();

    bool shouldClose() { return !running; }

    SDL_Window *getNativeWindow() { return nativeWindow; }

    int getWidth() const { return data.width; }

    int getHeight() const { return data.height; }

    std::string getTitle() const { return data.title; }

    void update();
    void updateSize(int width, int height);
    void close() { running = false; }

  private:
    bool running;
    WindowData data;
    SDL_Window *nativeWindow;
    SDL_GLContext glContext;
};
