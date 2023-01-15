#include "Window.hpp"

#include <iostream>

Window::Window(const std::string &title, int width, int height) : data({title, width, height})
{
    int sdlStatus = SDL_Init(SDL_INIT_VIDEO);

    if (sdlStatus < 0) throw std::exception("Couldn't initialize SDL!\n");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    nativeWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                                    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!nativeWindow) throw std::exception("Failed to create SDL window!\n");

    glContext = SDL_GL_CreateContext(nativeWindow);
    SDL_SetWindowData(nativeWindow, "Window", this);

    int gladStatus = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    if (!gladStatus) throw std::exception("Couldn't initialize GLAD!\n");

    std::cout << glGetString(GL_VERSION) << "\n";

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

Window::~Window()
{
    SDL_DestroyWindow(nativeWindow);
    SDL_Quit();
}

void Window::update() { glClear(GL_COLOR_BUFFER_BIT); }

void Window::updateSize(int width, int height)
{
    data.width  = width;
    data.height = height;

    glViewport(0, 0, width, height);
}
