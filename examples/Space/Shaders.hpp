#ifndef SPACE_SHADERS
#define SPACE_SHADERS

#define checkShader(shader)                                 \
{                                                           \
    GLint status;                                           \
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);      \
                                                            \
    if(status == -1) {                                      \
        char buffer[512];                                   \
        glGetShaderInfoLog(shader, 512, NULL, buffer);      \
                                                            \
        std::cout << buffer << std::endl;                   \
    } else {                                                \
        std::cout << #shader << " compiled successfuly!\n"; \
    }                                                       \
                                                            \
}

class Shaders {
public:
    static const char *vertexSource;
    static const char *fragmentSource;
};

#endif // SPACE_SHADERS