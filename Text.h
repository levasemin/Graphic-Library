#pragma once

#include <SFML/Graphics.hpp>
#include "Color.h"
#include "Font.h"

class Text
{
public:
    sf::Text text_;

    Text () {}
    
    Text (const Font &font) 
    {
        setFont(font);
    };

    void setFont(const Font &font)
    {
        text_.setFont(font.font_);
    }

    void setCharacterSize(int size)
    {
        text_.setCharacterSize(size);
    }
    
    void setString(const char *text)
    {
        text_.setString(text);
    }

    void setFillColor(Color color)
    {
        text_.setFillColor(color.get_sf_color());
    }

    Font getFont() 
    {
        return Font(*text_.getFont());
    }

private:
    friend class Label;
    friend class RenderTexture;
};