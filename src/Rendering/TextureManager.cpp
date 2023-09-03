#include "TextureManager.hpp"

namespace SL
{    
    TextureManager& TextureManager::getInstance()
    {
        static TextureManager instance;
        static bool first_time = true;

        if (first_time)
        {
            std::string path = LOCATION;
            path.erase(path.end() - 32, path.end());
            
            for (size_t i = 0; i < instance.textures_.size(); i++) 
            {
                instance.textures_[i].texture.loadFromFile((path + "resources/Textures/" + instance.textures_[i].path).c_str());
            }

            first_time = false;
        }

        return instance;
    }

    Texture &TextureManager::operator[](int icon)
    {
        return textures_[icon].texture;
    }
}