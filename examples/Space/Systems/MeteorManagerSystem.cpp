#include "MeteorManagerSystem.hpp"

#include <random>

#include "../Core/Input.hpp"
#include "../Core/TextureManager.hpp"
#include "../Core/Time.hpp"
#include "../World.hpp"

void MeteorManagerSystem::onUpdate()
{
    static float waveTime = 0.0f;
    waveTime += Time::DeltaTime;

    if(waveTime > 15.f)
    {
        waveTime = 0.0f;
        std::cout << "MeteorManager: Instancing new wave - " << currentWave << std::endl;
        for(int i = 0; i < currentWave; i++)
        {
            auto meteor = world->createEntity();

            world->addTag<EnemyTag>(meteor);

            auto &transform = world->addComponent<TransformComponent>(meteor);
            auto &rigidbody = world->addComponent<RigidBodyComponent>(meteor);
            auto &sprite    = world->addComponent<SpriteComponent>(meteor);
            auto &collider  = world->addComponent<CircleColliderComponent>(meteor);

            std::random_device rd;                               // obtain a random number from hardware
            std::mt19937 gen(rd());                              // seed the generator
            std::uniform_int_distribution<> distrPos(-400, 400); // define the range
            std::uniform_int_distribution<> distrScale(10, 50);  // define the rangev
            std::uniform_int_distribution<> distrAngle(0, 360);  // define the rangev

            auto x = (float)distrPos(gen);
            auto y = (float)distrPos(gen);

            auto angle = (float)distrAngle(gen);

            auto speed = (float)distrScale(gen);

            transform.position = {x, y, 0};
            transform.rotation = {0, 0, angle};
            transform.scale    = {1, 1, 1};

            rigidbody.velocity = glm::normalize(glm::vec3(x, y, 0)) * speed;
            rigidbody.mass     = 0.f;

            sprite.texture       = TextureManager::Get()->getTextureIndex("Resources/meteor.png");
            sprite.texturesCount = 1;
            collider.radius      = 32.f;
            collider.scale       = 0.9f;
        }

        int previous_wave = currentWave;
        currentWave       = nextWave;
        nextWave += previous_wave;
    }
}

void MeteorManagerSystem::onReceive(PlayerEndGameEvent event)
{
    currentWave = firstWave;
    nextWave    = secondWave;

    for(auto entity: getRegisteredEntities())
    {
        world->destroyEntity(entity);
    }
}
