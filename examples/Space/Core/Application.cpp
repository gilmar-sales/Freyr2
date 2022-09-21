#include "Application.hpp"
#include "Time.hpp"
#include <GLFW/glfw3.h>
#include <sstream>

Application *Application::instance = nullptr;

Application::Application() : window("Space", 800, 600), world(freyr::World()) {
    assert(!instance);
    instance = this;

    initPlayer();
    glfwSwapInterval(0);
}

void Application::run() {
    auto previousTime = (float) glfwGetTime();
    float frametimeAccumulator = 0;
    float frames = 0;
    while (!glfwWindowShouldClose(window.get_native_window())) {

        auto now = (float) glfwGetTime();
        Time::DeltaTime = now - previousTime;
        previousTime = now;

        frametimeAccumulator += Time::DeltaTime;
        frames += 1;

        if (frametimeAccumulator >= 1) {
            if (world.entities().getNextEntity()) {
                auto &player = world.addComponent<PlayerComponent>(0);
                std::stringstream ss;
                ss << window.getTitle() << " - " << frames << " FPS" << " - Lifes: " << player.lifes << " - Score: "
                   << player.score << " - Entities: ";
                ss << world.entities().getNextEntity();

                glfwSetWindowTitle(window.get_native_window(), ss.str().c_str());
            }

            frametimeAccumulator = 0;
            frames = 0;
        }

        window.update();

        world.update();
        glfwSwapBuffers(window.get_native_window());
    }
}

void Application::initPlayer() {
    auto ent = world.createEntity();

    auto &transform = world.addComponent<TransformComponent>(ent);
    auto &sprite = world.addComponent<SpriteComponent>(ent);
    auto &rigidbody = world.addComponent<RigidBodyComponent>(ent);
    auto &circleCollider = world.addComponent<CircleColliderComponent>(ent);
    auto &life = world.addComponent<PlayerComponent>(ent);
    auto &gun = world.addComponent<LaserGunComponent>(ent, {.maxShotsPerSecond = 8});
    world.addTag<PlayerTag>(ent);

    transform.scale = {1.f, 1.f, 1.f};

    sprite.texture = TextureManager::Get()->getTextureIndex("Resources/x_wing.png");
    sprite.texturesCount = 1;
    rigidbody.mass = 2;
    circleCollider.radius = 10;
    life.lifes = 4;
}

