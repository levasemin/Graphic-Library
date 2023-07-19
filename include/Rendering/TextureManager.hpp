#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include "Texture.hpp"

namespace SL
{
    class TextureManager
    {
    private:
        TextureManager(){}
        TextureManager(const TextureManager &source) = default;
        TextureManager &operator=(const TextureManager &source) = default;
        
    public:

        struct texture
        {
            std::string path;
            Texture texture;
        };

        enum Icon
        {
            RightArrow,
            LeftArrow,
            UpArrow,
            DownArrow,
            Swap
        };

        std::vector<texture> textures_ = 
        {
            {"RightArrow.png", Texture(Color::White)}, 
            {"LeftArrow.png", Texture(Color::White)},
            {"UpArrow.png", Texture(Color::White)},
            {"DownArrow.png", Texture(Color::White)},
            {"Swap.png", Texture(Color::White)}
        };

        
        void load_textures(std::string path);
        
        static TextureManager& getInstance();

        Texture &operator[](int icon);
    };
}