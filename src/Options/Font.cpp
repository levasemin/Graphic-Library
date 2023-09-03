#include "Font.hpp"

namespace SL
{
    #define FONT_PATH(name) std::string(LOCATION).erase(strlen(LOCATION) - 20, 20) + "resources/fonts/" + name + ".ttf"

    const Font Font::Arial                  (FONT_PATH("Arial"));
    const Font Font::Arial_Black            (FONT_PATH("Arial_Black"));
    const Font Font::Comic_Sans_MS          (FONT_PATH("Comic_Sans_MS"));
    const Font Font::Courier_New            (FONT_PATH("Courier_New"));
    const Font Font::Franklin_Gothic_Medium (FONT_PATH("Franklin_Gothic_Medium"));
    const Font Font::Georgia                (FONT_PATH("Georgia"));
    const Font Font::Impact                 (FONT_PATH("Impact"));
    const Font Font::Lucida_Console         (FONT_PATH("Lucida_Console"));
    const Font Font::Microsoft_Sans_Serif   (FONT_PATH("Microsoft_Sans_Serif"));
    const Font Font::Palatino_Linotype      (FONT_PATH("Palatino_Linotype"));
    const Font Font::Sylfaen                (FONT_PATH("Sylfaen"));
    const Font Font::Tahoma                 (FONT_PATH("Tahoma"));
    const Font Font::Times_New_Roman        (FONT_PATH("Times_New_Roman"));
    const Font Font::Trebuchet_MS           (FONT_PATH("Trebuchet_MS"));
    const Font Font::Verdana                (FONT_PATH("Verdana"));

    Font::Font (const sf::Font &font) : font_(font) 
    {}

    Font::Font (const char *filename) : font_()
    {
        font_.loadFromFile(filename);
    }

    Font::Font (const std::string &filename) : font_()
    {
        font_.loadFromFile(filename.c_str());
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