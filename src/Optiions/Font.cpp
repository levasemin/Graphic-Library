#include "Font.hpp"

namespace SL
{
    const Font Font::Times_new_roman ("../src/fonts/Times_New_Roman.ttf");
    
    Font::Font (const sf::Font &font) : font_(font) 
    {}

    Font::Font (const char *filename) : font_()
    {
        font_.loadFromFile(filename);
    }

    Texture Font::getTexture(unsigned int characterSize)
    {
        return Texture(font_.getTexture(characterSize));
    }

    bool Font::loadFromFile(const char *filename)
    {
        return font_.loadFromFile(filename);
    }    
}