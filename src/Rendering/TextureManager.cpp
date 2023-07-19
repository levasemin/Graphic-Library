#include "TextureManager.hpp"

namespace SL
{    
    void TextureManager::load_textures(std::string path)
    {
        std::stringstream skinNameStream;
        skinNameStream << path.c_str() << "/";
        
        for (size_t i = 0; i < textures_.size(); i++) 
        {
            textures_[i].texture.loadFromFile((skinNameStream.str() + textures_[i].path).c_str());
        }
    }
    
    TextureManager& TextureManager::getInstance()
    {
        static TextureManager instance;
        return instance;
    }

    Texture &TextureManager::operator[](int icon)
    {
        return textures_[icon].texture;
    }
}