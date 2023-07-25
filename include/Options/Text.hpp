#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#pragma once

#include <SFML/Graphics.hpp>
#include "Color.hpp"
#include "Font.hpp"
#include <string>

namespace SL
{
    class Text
    {
    public:
        Text ();
        
        Text (const Font &font);

        void setFont(const Font &font);

        void setCharacterSize(int size);
        
        int getCharacterSize();

        void setPosition(const Vector2d &position);

        Vector2d getGlobalBounds();

        void setString(const std::string &text);

        std::string getString();

        void setFillColor(const Color &color);

        void setColor(const Color &color);

        Font getFont();

        friend class Label;
        friend class RenderTexture;
    
    private:
        sf::Text text_;    
    };
}