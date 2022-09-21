#pragma once

#include "../World.hpp"
#include "Window.hpp"

class Application
{
  public:
    Application();

    ~Application() = default;

    static Application &Get()
    {
        return *instance;
    }

    static freyr::World &getWorld()
    {
        return instance->world;
    }

    void run();

    void initPlayer();

    Window &getWindow()
    {
        return window;
    }

  private:
    Window window;
    freyr::World world;
    static Application *instance;
};
