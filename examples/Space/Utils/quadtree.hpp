#pragma once

#include <functional>
#include <memory>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct ColliderData
{
    unsigned id;
    glm::vec2 position;
    float radius;
};

class QuadTree
{
  public:
    QuadTree(glm::vec2 position, float half_range, unsigned capacity);

    ~QuadTree() = default;

    bool insert(ColliderData entity);

    void subdivide();

    void query(ColliderData entity, std::vector<ColliderData> *found);

    bool contains(ColliderData entity);

    bool collide(ColliderData first, ColliderData second);

    bool intersect(ColliderData entity);

    void draw(unsigned vao, unsigned shaderProgram);

  private:
    glm::vec2 m_position{};
    float m_half_range;
    std::vector<ColliderData> m_elements;
    unsigned m_capacity;

    std::unique_ptr<QuadTree> m_top_left;
    std::unique_ptr<QuadTree> m_top_right;
    std::unique_ptr<QuadTree> m_bot_left;
    std::unique_ptr<QuadTree> m_bot_right;
};
