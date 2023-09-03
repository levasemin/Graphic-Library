#include "Label.hpp"

namespace SL
{
    Label::Label(Vector2d shape, Vector2d position, const Texture &texture) : 
        Object(shape, position, texture), 
        text_()
    {
        text_.setFont(Font::Times_New_Roman);
        text_.setColor(Color::Black);
    };
    
    void Label::setText(const Text &text)
    {
        text_ = text;
        redraw();
    }
    
    void Label::setText(const std::string &string)
    {
        text_.setString(string.c_str());
        redraw();
    }

    std::string Label::getText()
    {
        return text_.getString();
    }
    
    void Label::setAlignment(Alignment type)
    {
        alignment_ = type;
    }

    void Label::setCharacterSize(int text_size)
    {
        text_.setCharacterSize(text_size);
        redraw();
    }
    
    void Label::setTextColor(const Color &color)
    {
        text_.setColor(color.get_sf_color());
    }

    void Label::redraw()
    {
        getRenderTexture()->clear();
        Sprite sprite(getRenderTexture()->getSize(), getTexture());
        getRenderTexture()->draw(sprite);

        Vector2d text_position(0, 0);

        Vector2d text_shape = text_.getGlobalBounds();
        text_shape.y_ = text_shape.y_ > float(text_.getCharacterSize()) ? text_shape.y_ : float(text_.getCharacterSize()) / 10 * 7;

        switch (alignment_)
        {
            case Alignment::CenterCenter:
            {
                text_position.x_ = getShape().x_ / 2 - text_shape.x_ / 2;
                text_position.y_ = getShape().y_ / 2 - text_shape.y_; 
                break;
            }

            case Alignment::LeftCenter:
            {
                text_position.x_ = 0;
                text_position.y_ = getShape().y_ / 2 - text_shape.y_; 
                break;
            }

            case Alignment::LeftDown:
            {
                text_position.x_ = 0;
                text_position.y_ = getShape().y_ - text_shape.y_ * 2; 
                break;
            }
            case Alignment::LeftUp:
            {
                text_position.x_ = 0;
                text_position.y_ = -text_shape.y_ / 2; 
                break;
            }
            case Alignment::RightCenter:
            {
                text_position.x_ = getShape().x_ - text_shape.x_;
                text_position.y_ = getShape().y_ / 2 - text_shape.y_; 
                break;
            }
            case Alignment::RightDown:
            {
                text_position.x_ = getShape().x_ - text_shape.x_;
                text_position.y_ = getShape().y_ - text_shape.y_ * 2; 
                break;
            }
            case Alignment::RightUp:
            {
                text_position.x_ = getShape().x_ - text_shape.x_;
                text_position.y_ = -text_shape.y_ / 2;
            }
            default:
                break;
        }
        
        text_.setPosition(text_position);
        
        getRenderTexture()->draw(text_); 

        getRenderTexture()->display();
    }
}