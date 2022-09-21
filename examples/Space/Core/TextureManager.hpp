#pragma once

#include "../Utils/stb_image.h"

#include <unordered_map>
#include <utility>

class TextureManager
{
  public:
    static TextureManager *Get()
    {
        static auto *instance = new TextureManager();

        return instance;
    }

    unsigned getTextureIndex(const std::string &path);

  private:
    TextureManager()  = default;
    ~TextureManager() = default;

    static std::tuple<unsigned char *, int, int, int> openTextureFile(const std::string &path);
    static unsigned createTextureId(unsigned char *textureData, int width, int height, int channels);

    std::unordered_map<std::string, unsigned> texturesMap;
};
