#pragma once

#include "SFML/Graphics.hpp"
#include "Texture.hpp"

namespace SL
{
    class Font
    {

    public:

        sf::Font font_;

        static const Font Times_new_roman;
        
        Font (const sf::Font &font);

        Font (const char *filename);

        Texture getTexture(unsigned int characterSize);
        
        bool loadFromFile(const char *filename);

        friend class Text;
    };
}