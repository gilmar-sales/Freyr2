#include "RenderSystem.hpp"

#include "../Components/SpriteComponent.hpp"
#include "../Core/Application.hpp"

RenderSystem::RenderSystem(): color(1.0f, 1.0f, 1.0f)
{
    // Initialize Sprite Quad Mesh
    float vertices[] = {
        // positions          // colors           // texture coords (note that we changed them to 2.0f!)
        1.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // top right
        1.0f,  -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // bottom right
        -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -1.0f, 1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // top left
    };

    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &spriteVao);
    glBindVertexArray(spriteVao);

    glGenBuffers(1, &spriteVbo);

    glBindBuffer(GL_ARRAY_BUFFER, spriteVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &spriteEbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, spriteEbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Initialize shaders
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &Shaders::vertexSource, nullptr);
    glCompileShader(vertexShader);
    checkShader(vertexShader)

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &Shaders::fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    checkShader(fragmentShader)

        shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    int success;
    char infoLog[512];
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);

    glm::mat4 projection = glm::mat4(1.0f);

    projection = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, -1000.0f, 1000.0f);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
}

void RenderSystem::updateProjection() const
{
    float half_width     = (float)Application::Get().getWindow().getWidth() / 2;
    float half_height    = (float)Application::Get().getWindow().getHeight() / 2;
    glm::mat4 projection = glm::mat4(1.0f);

    projection = glm::ortho(-half_width, half_width, -half_height, half_height, -1000.0f, 1000.0f);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
}

RenderSystem::~RenderSystem()
{
    glDeleteBuffers(1, &spriteEbo);
    glDeleteBuffers(1, &spriteVbo);
    glDeleteVertexArrays(1, &spriteVao);
    glDeleteProgram(shaderProgram);
}

void RenderSystem::onUpdate()
{
    updateProjection();
    for(unsigned int entity: getRegisteredEntities())
    {
        auto &transform = world->getComponent<TransformComponent>(entity);
        auto &sprite    = world->getComponent<SpriteComponent>(entity);

        glm::mat4 model = glm::mat4(1.0f);
        model           = glm::translate(model, transform.position);
        model           = glm::scale(model, transform.scale * SPRITE_SIZE);
        model           = glm::rotate(model, glm::radians(transform.rotation.z), {0, 0, 1});

        if(sprite.texturesCount > 1)
        {
            sprite.frameTime += Time::DeltaTime;

            if(sprite.frameTime > 0.1f)
            {
                sprite.currentFrame += 1;
                if(sprite.currentFrame >= sprite.texturesCount)
                {
                    sprite.currentFrame = 0;
                }
            }
            float slice      = 1.0f / (float)sprite.texturesCount;
            float leftCoord  = slice * (float)sprite.currentFrame;
            float rightCoord = leftCoord + slice;

            float textureCoord[] = {
                rightCoord, 1.0f, // top right
                rightCoord, 0.0f, // bottom right
                leftCoord,  0.0f, // bottom left
                leftCoord,  1.0f  // top left
            };

            glUniform2fv(glGetUniformLocation(shaderProgram, "textureCoord"), 4, &textureCoord[0]);
        }
        else
        {
            static float defaultTextureCoord[] = {
                1.0f, 1.0f, // top right
                1.0f, 0.0f, // bottom right
                0.0f, 0.0f, // bottom left
                0.0f, 1.0f  // top left
            };
            glUniform2fv(glGetUniformLocation(shaderProgram, "textureCoord"), 4, &defaultTextureCoord[0]);
        }

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
        glUniform3fv(glGetUniformLocation(shaderProgram, "color"), 1, &color[0]);
        glBindVertexArray(spriteVao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sprite.texture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    glBindVertexArray(0);
}