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
        Texture () = default;
        Texture(const char *path);
        Texture (const Color &color);
        Texture (const sf::Texture &texture);

        Texture (const Texture &) = default;
        Texture& operator= (const Texture &) = default; 
        ~Texture() = default;
                
        bool loadFromFile(const char *path);

        Vector2d getSize() const;

        Image copyToImage();

        friend class Sprite;
        friend class Image;
    private:
        sf::Texture texture_;    

    };
}