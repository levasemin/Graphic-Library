#pragma once

#include <SFML/Graphics.hpp>

#include "Vector2d.hpp"
#include "Color.hpp"

namespace SL
{
    class Image;

    class Texture
    {
        
    public:
        sf::Texture texture_;    
        
        Texture () = default;
        Texture (const Texture &) = default;
        Texture& operator= (const Texture &) = default; 
        ~Texture() = default;
        
        Texture(const char *path);
        
        Texture (const Color &color);

        Texture (const sf::Texture &texture);
        
        bool loadFromFile(const char *path);

        Vector2d getSize() const;

        Image copyToImage();

    private:
        friend class Sprite;
    };
}