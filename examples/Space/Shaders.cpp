#include "Shaders.hpp"

const char *Shaders::vertexSource = R"glsl(
            #version 330 core
            layout (location = 0) in vec3 position;
            layout (location = 1) in vec3 color;
            layout (location = 2) in vec2 texture_coord;

            uniform mat4 projection;
            uniform mat4 model;
            uniform vec2 textureCoord;

            out vec3 Color;
            out vec2 TexCoord;

            void main()
            {
                gl_Position = projection * model * vec4(position, 1.0);
                Color = color;
                TexCoord = texture_coord;
            }
        )glsl";

const char *Shaders::fragmentSource = R"glsl(
            #version 330 core
            uniform sampler2D Texture;

            in vec3 Color;
            in vec2 TexCoord;

            out vec4 outColor;

            void main()
            {
                vec4 texColor = texture(Texture, TexCoord);

                if(texColor.a < 0.1)
                    discard;

                outColor = texColor * vec4(Color, 1.0);
            }
        )glsl";
