#include "TextureManager.hpp"
#include <glad/glad.h>

unsigned TextureManager::getTextureIndex(const std::string& path) {
    if (texturesMap.contains(path)) {
        return texturesMap.at(path);
    }

    auto [data, width, height, channels] = openTextureFile(path);
    if (data != nullptr) {
        unsigned textureId = createTextureId(data, width, height, channels);

        texturesMap.insert(std::make_pair(path, textureId));

        return textureId;
    }

    return -1;
}

std::tuple<unsigned char *, int, int, int > TextureManager::openTextureFile(const std::string& path) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        std::cout << "Texture loaded: " << path << " - " << width << ", " << height << " : " << nrChannels << std::endl;
        return {data, width, height, nrChannels};
    }

    std::cout << "Failed to load texture: " << path << std::endl;
    return {nullptr, 0, 0, 0};
}

unsigned TextureManager::createTextureId(unsigned char *textureData, int width, int height, int channels) {
    unsigned textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    int channel_type = GL_NONE;

    switch (channels) {
        case 3: channel_type = GL_RGB;
                break;
        case 4: channel_type = GL_RGBA;
                break;
        default:
            break;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, channel_type, width, height, 0, channel_type, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    return textureId;
}
