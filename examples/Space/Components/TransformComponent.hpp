#ifndef FREYR_SPACE_TRANSFORM_COMPONENT_HPP
#define FREYR_SPACE_TRANSFORM_COMPONENT_HPP

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

struct TransformComponent {
    glm::vec3 position = {0, 0, 0};
    glm::vec3 scale = {1, 1, 1};
    glm::vec3 rotation = {0, 0, 0};

    glm::vec3 getForwardDirection() {
        glm::vec4 front = {0, 1, 0, 0};
        glm::mat4 rotationMatrix = {
                {1, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}};
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), {0, 0, 1});
        front = front * rotationMatrix;

        return glm::normalize(glm::vec3(-front.x, front.y, front.z));
    }

    glm::vec3 getRightDirection() {
        glm::vec4 front = {1, 0, 0, 0};
        glm::mat4 rotationMatrix = {
                {1, 0, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1}};
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), {0, 0, 1});
        front = front * rotationMatrix;

        return glm::normalize(glm::vec3(front.x, -front.y, front.z));
    }
};

#endif // FREYR_SPACE_TRANSFORM_COMPONENT_HPP
