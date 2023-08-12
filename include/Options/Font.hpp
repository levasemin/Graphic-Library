#pragma once

#include <SFML/Graphics.hpp>

#include "Texture.hpp"

namespace SL
{
    class Font
    {
    public:
        static const Font Times_new_roman;
        
        Font (const sf::Font &font);
        Font (const char *filename);
        Font(const Font &source) = default;
        Font &operator= (const Font &source) = default;
        ~Font() = default;
        
        Texture getTexture(unsigned int characterSize);
        
        bool loadFromFile(const char *filename);

        friend class Text;
    private:
        sf::Font font_;

    };
}