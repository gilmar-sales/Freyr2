#include "PlayerMoveSystem.hpp"
#include "../World.hpp"
#include <format>
#include <sstream>

void PlayerMoveSystem::onUpdate() {
    for (auto entity: getRegisteredEntities()) {
        auto[transform, rigidbody, player] = world->getComponents<
                TransformComponent, RigidBodyComponent, PlayerComponent
        >(entity);

        if (Input::IsKeyPressed(Key::W)) {
            auto leftBoost = createBoost(entity);
            auto rightBoost = createBoost(entity);
            glm::vec3 forward = transform.getForwardDirection();

            rigidbody.velocity += forward * 300.f * Time::DeltaTime;
            placeBoost(entity, leftBoost, rightBoost);
        }

        if (Input::IsKeyPressed(Key::A)) {
            transform.rotation.z += 90 * Time::DeltaTime;
        } else if (Input::IsKeyPressed(Key::D)) {
            transform.rotation.z -= 90 * Time::DeltaTime;
        }

    }
}

freyr::EntityID PlayerMoveSystem::createBoost(freyr::EntityID owner) {
    static float frameTime = 0;
    static unsigned frame = 1;
    auto boost = world->createEntity();

    frameTime += Time::DeltaTime;

    if(frameTime > 0.1f) {
        frameTime = 0;
        frame = frame >= 4 ? 1 : frame + 1;
    }

    std::stringstream builder;
    builder << "Resources/boost";
    builder << frame;
    builder << ".png";
    world->addComponents<TransformComponent, SpriteComponent, DecayComponent>(boost, {
            .scale = {0.4f, 0.6f, 0.6f},
        }, {
            .width = 64,
            .height = 64,
            .texture = TextureManager::Get()->getTextureIndex(builder.str()),
            .texturesCount = 1
        }, {
        .maxTime = Time::DeltaTime * 4,
        .current = 0
        }
    );

    return boost;
}

freyr::EntityID PlayerMoveSystem::placeBoost(freyr::EntityID owner, freyr::EntityID leftBoost, freyr::EntityID rightBoost) {
    auto &ownerTransform = world->getComponent<TransformComponent>(owner);
    auto &leftTransform = world->getComponent<TransformComponent>(leftBoost);
    auto &rightTransform = world->getComponent<TransformComponent>(rightBoost);

    leftTransform.rotation = ownerTransform.rotation;
    rightTransform.rotation = ownerTransform.rotation;

    auto leftOffset = ownerTransform.getRightDirection() * -8.f;
    auto rightOffset = ownerTransform.getRightDirection() * 8.f;

    leftTransform.position = leftOffset + ownerTransform.position - ownerTransform.getForwardDirection() * 28.f;
    rightTransform.position = rightOffset + ownerTransform.position - ownerTransform.getForwardDirection() * 28.f;

    return 0;
}

