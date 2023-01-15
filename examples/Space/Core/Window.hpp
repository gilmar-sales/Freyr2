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

    bool shouldClose() { return SDL_QuitRequested(); };

    SDL_Window *getNativeWindow() { return nativeWindow; }

    int getWidth() const { return data.width; }

    int getHeight() const { return data.height; }

    std::string getTitle() const { return data.title; }

    void update();
    void updateSize(int width, int height);

  private:
    WindowData data;
    SDL_Window *nativeWindow;
    SDL_GLContext glContext;
};
