#pragma once

#include <SFML/Graphics.hpp>

#include "Texture.hpp"
#include <cstring>

namespace SL
{
    #define LOCATION (char *)__FILE__

    class Font
    {
    public:
        static const Font Arial;
        static const Font Arial_Black;
        static const Font Comic_Sans_MS;
        static const Font Courier_New;
        static const Font Franklin_Gothic_Medium;
        static const Font Georgia;
        static const Font Impact;
        static const Font Lucida_Console;
        static const Font Microsoft_Sans_Serif;
        static const Font Palatino_Linotype;
        static const Font Sylfaen;
        static const Font Tahoma;
        static const Font Times_New_Roman;
        static const Font Trebuchet_MS;
        static const Font Verdana;

        Font (const sf::Font &font);
        Font (const char *filename);
        Font (const std::string &filename);

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