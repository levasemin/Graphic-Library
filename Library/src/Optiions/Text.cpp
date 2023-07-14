#include "Text.hpp"

namespace SL
{
    Text::Text ():
        text_()
    {}
    
    Text::Text (const Font &font): 
        text_()
    {
        setFont(font);
    };

    void Text::setFont(const Font &font)
    {
        text_.setFont(font.font_);
    }

    void Text::setCharacterSize(int size)
    {
        text_.setCharacterSize(size);
    }
    
    int Text::getCharacterSize()
    {
        return text_.getCharacterSize();
    }

    void Text::setPosition(const Vector2d &position)
    {
        text_.setPosition(position.x_, position.y_);
    }

    Vector2d Text::getGlobalBounds()
    {
        return Vector2d(text_.getGlobalBounds().width, text_.getGlobalBounds().height);
    }

    void Text::setString(const std::string &text)
    {
        text_.setString(text);
    }

    std::string Text::getString()
    {
        return std::string(text_.getString());
    }

    void Text::setFillColor(const Color &color)
    {
        text_.setFillColor(color.get_sf_color());
    }
    
    void Text::setColor(const Color &color)
    {
        const sf::Color &sf_color = color.get_sf_color();
        text_.setColor(sf_color);
    }

    Font Text::getFont() 
    {
        return Font(*text_.getFont());
    }

}