#ifndef FREYR_EXAMPLE_DESIGN_HPP
#define FREYR_EXAMPLE_DESIGN_HPP

#include "Components.hpp"
#include "Tags.hpp"

using ComponentList = std::tuple<
        BulletComponent,
        CircleColliderComponent,
        DecayComponent,
        LaserGunComponent,
        MeshComponent,
        NameComponent,
        PlayerComponent,
        RigidBodyComponent,
        SpriteComponent,
        TransformComponent
        >;

using TagList = std::tuple<PlayerTag, EnemyTag, BulletTag>;

#include <Freyr/Core/Design.hpp>

using Design = freyr::Design<ComponentList, TagList>;

#endif //FREYR_EXAMPLE_DESIGN_HPP
