#pragma once

#include <SFML/Graphics.hpp>
#include "Color.h"

class Text
{
public:
    Text() {};

    void setFont(const char *path)
    {
        sf::Font font;
        font.loadFromFile(path);
        text_.setFont(font);
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

private:
    sf::Text text_;
    friend class Label;
    friend class RenderTexture;
};