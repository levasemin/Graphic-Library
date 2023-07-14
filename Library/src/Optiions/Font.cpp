#include "Font.hpp"

namespace SL
{
    const char *TIMES_NEW_ROMAN_FONT = "fonts/Times_New_Roman.ttf";

    const Font Font::Times_new_roman (TIMES_NEW_ROMAN_FONT);
    
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