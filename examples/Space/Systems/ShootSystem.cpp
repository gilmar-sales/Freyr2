#include "ShootSystem.hpp"
#include "../World.hpp"

void ShootSystem::onUpdate() {
    for (unsigned int entity: getRegisteredEntities()) {
        auto &transform = world->getComponent<TransformComponent>(entity);
        auto &rigidbody = world->getComponent<RigidBodyComponent>(entity);
        auto &gun = world->getComponent<LaserGunComponent>(entity);

        if(Input::GetKeyUp(Key::Space)) {
            gun.triggered = false;
            gun.time = 0;
        }

        if (Input::GetKeyDown(Key::Space)) {
            gun.triggered = true;
            gun.time = 1;
        }

        if (gun.triggered) {
            gun.time += Time::DeltaTime;

            float shotRatio = 1.0f / (float) gun.maxShotsPerSecond;
            bool canShot = gun.time >= shotRatio;

            if(canShot) {
                glm::vec3 forward = transform.getForwardDirection();
                glm::vec3 right = transform.getRightDirection();

                auto left_bullet = createBullet(entity);

                auto &left_bullet_transform = world->addComponent<TransformComponent>(left_bullet);
                left_bullet_transform.position = transform.position + glm::normalize(forward - right) * 40.f;

                auto right_bullet = createBullet(entity);
                auto &right_bullet_transform = world->addComponent<TransformComponent>(right_bullet);
                right_bullet_transform.position = transform.position + glm::normalize(forward + right) * 40.f;
            }

            if(gun.time > shotRatio) {
                gun.time = 0;
            }
        }
    }
}

freyr::EntityID ShootSystem::createBullet(freyr::EntityID owner)  {
    auto &transform = world->getComponent<TransformComponent>(owner);

    auto bullet = world->createEntity();

    auto &bullet_transform = world->addComponent<TransformComponent>(bullet);
    auto &bullet_rigidbody = world->addComponent<RigidBodyComponent>(bullet);
    auto &bullet_sprite = world->addComponent<SpriteComponent>(bullet);
    auto &bullet_decay = world->addComponent<DecayComponent>(bullet);
    auto &bullet_collider = world->addComponent<CircleColliderComponent>(bullet);
    auto &bullet_comp = world->addComponent<BulletComponent>(bullet);

    world->addTag<BulletTag>(bullet);
    glm::vec3 forward = transform.getForwardDirection();

    bullet_transform.rotation = transform.rotation;
    bullet_transform.scale = {0.5f, 0.5f, 0.5f};
    bullet_rigidbody.velocity = forward * 500.f;
    bullet_rigidbody.mass = 0;

    bullet_sprite.texture = TextureManager::Get()->getTextureIndex("resources/laser_shot.png");
    bullet_sprite.texturesCount = 1;

    bullet_decay.maxTime = 0.8f;
    bullet_decay.current = 0.f;
    bullet_collider.radius = 5;
    bullet_comp.owner = owner;

    return bullet;
}