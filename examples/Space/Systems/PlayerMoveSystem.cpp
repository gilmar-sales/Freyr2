#include "PlayerMoveSystem.hpp"

#include <sstream>

#include "../Core/TextureManager.hpp"
#include "../Events/InputEvents.hpp"
#include "../World.hpp"

void PlayerMoveSystem::onUpdate()
{
    for (auto entity : getRegisteredEntities())
    {
        auto [transform, rigidbody, player] =
            world->getComponents<TransformComponent, RigidBodyComponent, PlayerComponent>(entity);

        if (m_velocity > 0.f)
        {
            glm::vec3 forward = transform.getForwardDirection();
            rigidbody.velocity += forward * m_velocity * Time::DeltaTime;

            auto leftBoost  = createBoost(entity);
            auto rightBoost = createBoost(entity);

            placeBoost(entity, leftBoost, rightBoost);
        }

        transform.rotation.z += m_turnVelocity * Time::DeltaTime;
    }
}

void PlayerMoveSystem::onReceive(const KeyPressedEvent &event)
{
    if (event.key == Key::A)
    {
        m_turnVelocity = 90.f * event.value;
    }
    else if (event.key == Key::D)
    {
        m_turnVelocity = -90.f * event.value;
    }
    else if (event.key == Key::W)
    {
        m_velocity = 300.f * event.value;
    }
}

freyr::EntityID PlayerMoveSystem::createBoost(freyr::EntityID owner)
{
    static float frameTime = 0;
    static unsigned frame  = 1;
    auto boost             = world->createEntity();

    frameTime += Time::DeltaTime;

    if (frameTime > 0.1f)
    {
        frameTime = 0;
        frame     = frame >= 4 ? 1 : frame + 1;
    }

    std::stringstream builder;
    builder << "Resources/boost";
    builder << frame;
    builder << ".png";
    world->addComponents<TransformComponent, SpriteComponent, DecayComponent>(
        boost,
        {
            .scale = {0.4f, 0.6f, 0.6f},
    },
        {.width         = 64,
         .height        = 64,
         .texture       = TextureManager::Get()->getTextureIndex(builder.str()),
         .texturesCount = 1},
        {.maxTime = Time::DeltaTime * 4, .currentTime = 0});

    return boost;
}

freyr::EntityID PlayerMoveSystem::placeBoost(freyr::EntityID owner, freyr::EntityID leftBoost,
                                             freyr::EntityID rightBoost)
{
    auto &ownerTransform = world->getComponent<TransformComponent>(owner);
    auto &leftTransform  = world->getComponent<TransformComponent>(leftBoost);
    auto &rightTransform = world->getComponent<TransformComponent>(rightBoost);

    leftTransform.rotation  = ownerTransform.rotation;
    rightTransform.rotation = ownerTransform.rotation;

    auto leftOffset  = ownerTransform.getRightDirection() * -8.f;
    auto rightOffset = ownerTransform.getRightDirection() * 8.f;

    leftTransform.position  = leftOffset + ownerTransform.position - ownerTransform.getForwardDirection() * 28.f;
    rightTransform.position = rightOffset + ownerTransform.position - ownerTransform.getForwardDirection() * 28.f;

    return 0;
}
