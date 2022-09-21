#ifndef SPACE_ECS_RENDER_SYSTEM_HPP
#define SPACE_ECS_RENDER_SYSTEM_HPP

#include <Freyr/Core/BaseSystem.hpp>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Shaders.hpp"

constexpr float SPRITE_SIZE = 32.0f;
struct TransformComponent;
struct SpriteComponent;

class RenderSystem : public freyr::BaseSystem {
public:
    using Signature = std::tuple<TransformComponent, SpriteComponent>;

    RenderSystem();

    ~RenderSystem();

    void onUpdate() override;

private:
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;
    GLuint spriteVao;
    GLuint spriteVbo;
    GLuint spriteEbo;
    glm::vec3 color;

    void updateProjection() const;
};


#endif
