#pragma once

#include "Texture.h"
#include <iostream>
#include <string>
#include <sstream>
#include <map>

class TextureManager
{
private:
    TextureManager(){}
    TextureManager(const TextureManager &source) = default;
    TextureManager &operator=(const TextureManager &source) = default;
    
public:

    std::map<std::string, Texture> textures_ = 
    {
        {"RightArrow", Texture(Color::White)}, 
        {"LeftArrow", Texture(Color::White)},
        {"UpArrow", Texture(Color::White)},
        {"DownArrow", Texture(Color::White)}, 
    };

    
    void load_textures(std::string path)
    {
        std::stringstream skin;
        std::stringstream skinNameStream;
        skinNameStream << path.c_str() << "/";
        
        for (auto & name : textures_) 
        {
            textures_[name.first].loadFromFile((skinNameStream.str() + name.first + ".png").c_str());
        }
    }
    
    static TextureManager& getInstance()
    {
        static TextureManager instance;
        return instance;
    }

    Texture &operator[](const std::string &name)
    {
        return textures_[name];
    }
};