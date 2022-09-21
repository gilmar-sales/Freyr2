#ifndef FREYR_SPACE_RIGIDBODY_COMPONENT_HPP
#define FREYR_SPACE_RIGIDBODY_COMPONENT_HPP

#include <glm/glm.hpp>

struct RigidBodyComponent {
    glm::vec3 velocity;
    float mass;
};

#endif // FREYR_SPACE_RIGIDBODY_COMPONENT_HPP
