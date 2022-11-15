#pragma once

#include "Vector2d.h"
#include "Color.h"
#include <SFML/Graphics.hpp>

class Texture
{
    
public:
    sf::Texture texture_;    
    
    Texture ()
    {}

    Texture(const char *path) 
    {
        texture_.loadFromFile(path);
    };
    
    Texture (const Color &color)
    {
        sf::Image image;
        image.create(100, 100, color.get_sf_color());
        texture_.loadFromImage(image);
    }
    

    Texture (const Texture &texture)
    {
        texture_ = texture.texture_;
    }

    Texture (const sf::Texture &texture)
    {
        texture_ = texture;
    }

    Vector2d getSize() const
    {
        return Vector2d(texture_.getSize());
    }    

private:

    friend class Sprite;
};