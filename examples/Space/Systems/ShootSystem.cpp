#include "ShootSystem.hpp"

#include "../Core/TextureManager.hpp"
#include "../Core/Time.hpp"

#include "../World.hpp"

void ShootSystem::onReceive(const KeyDownEvent &event)
{
    if (event.key == Key::SPACE)
    {
        for (unsigned int entity : getRegisteredEntities())
        {
            auto [transform, rigidbody, laserGun] =
                world->getComponents<TransformComponent, RigidBodyComponent, LaserGunComponent>(entity);

            bool canShot = laserGun.ammoSpent < laserGun.ammo;

            if (canShot)
            {
                laserGun.ammoSpent += 1;
                laserGun.lastShootTime = Time::Now;

                glm::vec3 forward = transform.getForwardDirection();
                glm::vec3 right   = transform.getRightDirection();

                auto leftBullet = createBullet(entity);

                auto &leftBulletTransform    = world->addComponent<TransformComponent>(leftBullet);
                leftBulletTransform.position = transform.position + glm::normalize(forward - right) * 40.f;

                auto rightBullet              = createBullet(entity);
                auto &rightBulletTransform    = world->addComponent<TransformComponent>(rightBullet);
                rightBulletTransform.position = transform.position + glm::normalize(forward + right) * 40.f;
            }

            if (Time::Now - laserGun.lastShootTime >= laserGun.reloadTime)
            {
                laserGun.ammoSpent = 0;
            }
        }
    }
}

freyr::EntityID ShootSystem::createBullet(freyr::EntityID owner)
{
    auto &transform = world->getComponent<TransformComponent>(owner);

    auto bullet = world->createEntity();

    auto [bulletTransform, bulletRigidbody, bulletSprite, bulletDecay, bulletCollider, bulletComp] =
        world->addComponents<TransformComponent, RigidBodyComponent, SpriteComponent, DecayComponent,
                             CircleColliderComponent, BulletComponent>(bullet);

    world->addTag<BulletTag>(bullet);
    glm::vec3 forward = transform.getForwardDirection();

    bulletTransform.rotation = transform.rotation;
    bulletTransform.scale    = {0.5f, 0.5f, 0.5f};

    bulletRigidbody.velocity = forward * 500.f;
    bulletRigidbody.mass     = 0;

    bulletSprite.texture       = TextureManager::Get()->getTextureIndex("Resources/laser_shot.png");
    bulletSprite.texturesCount = 1;

    bulletDecay.maxTime     = 0.8f;
    bulletDecay.currentTime = 0.f;

    bulletCollider.radius = 5;
    bulletComp.owner      = owner;

    return bullet;
}