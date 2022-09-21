#ifndef SPACE_APPLICATION_HPP
#define SPACE_APPLICATION_HPP

#include "Window.hpp"
#include "../World.hpp"

class Application {
public:
    Application();

    ~Application() = default;

    static Application &Get() { return *instance; }

    static freyr::World &getWorld() { return instance->world; }

    void run();

    void initPlayer();


    Window &getWindow() { return window; }

private:
    Window window;
    freyr::World world;
    static Application *instance;

};

#endif // SPACE_APPLICATION_HPP
