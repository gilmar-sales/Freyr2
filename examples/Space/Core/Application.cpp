#include "Application.hpp"

#include <sstream>

#include "TextureManager.hpp"
#include "Time.hpp"

Application *Application::instance = nullptr;

Application::Application() : window("Space", 800, 600), world(freyr::World())
{
    assert(!instance);
    instance = this;

    initPlayer();
}

void Application::run()
{
    auto previousTime          = SDL_GetTicks() * 1e-3f;
    float frametimeAccumulator = 0;
    float frames               = 0;
    while (!window.shouldClose())
    {
        auto now  = SDL_GetTicks() * 1e-3f;
        Time::Now = now;

        Time::DeltaTime = now - previousTime;
        previousTime    = now;

        frametimeAccumulator += Time::DeltaTime;
        frames += 1;

        if (frametimeAccumulator >= 1)
        {
            if (world.entities().getNextEntity())
            {
                auto &player = world.addComponent<PlayerComponent>(0);
                std::stringstream ss;
                ss << window.getTitle() << " - " << frames << " FPS"
                   << " - Lifes: " << player.lifes << " - Score: " << player.score << " - Entities: ";
                ss << world.entities().getNextEntity();

                SDL_SetWindowTitle(window.getNativeWindow(), ss.str().c_str());
            }

            frametimeAccumulator = 0;
            frames               = 0;
        }

        window.update();

        world.update();
        SDL_GL_SwapWindow(window.getNativeWindow());
    }
}

void Application::initPlayer()
{
    auto ent = world.createEntity();

    auto &transform      = world.addComponent<TransformComponent>(ent);
    auto &sprite         = world.addComponent<SpriteComponent>(ent);
    auto &rigidbody      = world.addComponent<RigidBodyComponent>(ent);
    auto &circleCollider = world.addComponent<CircleColliderComponent>(ent);
    auto &life           = world.addComponent<PlayerComponent>(ent);
    auto &gun            = world.addComponent<LaserGunComponent>(ent, {});
    world.addTag<PlayerTag>(ent);

    transform.scale = {1.f, 1.f, 1.f};

    sprite.texture        = TextureManager::Get()->getTextureIndex("Resources/x_wing.png");
    sprite.texturesCount  = 1;
    rigidbody.mass        = 2;
    circleCollider.radius = 10;
    life.lifes            = 4;
}
