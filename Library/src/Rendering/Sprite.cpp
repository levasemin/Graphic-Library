#include "Sprite.hpp"

namespace SL
{
    Sprite::Sprite(Vector2d shape, const Texture &texture, int mode):
        mode_(mode),
        shape_(shape),
        texture_(texture), 
        sprite_()
    {
        setTexture(texture_);
    };

    Sprite::Sprite(sf::Sprite sprite):
        mode_(0),
        shape_(float(sprite.getTextureRect().width)  * sprite.getScale().x,
              float(sprite_.getTextureRect().height) * sprite.getScale().y),
        texture_(*sprite.getTexture()),
        sprite_(sprite)
    {
    }
    
    void Sprite::setTextureRect(Vector2d start, Vector2d end)
    {
        sprite_.setTextureRect(sf::IntRect((int)start.x_, (int)start.y_, (int)end.x_, (int)end.y_));
    }
    
    Vector2d Sprite::getShape()
    {
        return shape_;
    }
    
    void Sprite::setShape(Vector2d shape, bool with_rescale)
    {
        shape_ = shape;
        
        if (with_rescale)
        {
            rescale();
            setTexture(texture_);
        }
    }
    
    Texture Sprite::getTexture()
    {
        return texture_;
    }

    Color Sprite::getColor()
    {
        return Color(sprite_.getColor());
    }
    
    void Sprite::setColor(const Color &color)
    {
        sprite_.setColor(color.get_sf_color());
    }

    void Sprite::setTexture(const Texture &texture, bool resetRect)
    {
        texture_ = texture;
        sprite_.setTexture(texture_.texture_, resetRect);
        
        if (resetRect) 
        {
            rescale();
        }
    }

    void Sprite::setPosition(Vector2d position)
    {
        sprite_.setPosition(sf::Vector2f(position.x_, position.y_));
    }

    void Sprite::rescale()
    {
        float scale_x = shape_.x_ / float(sprite_.getTexture()->getSize().x);
        float scale_y = shape_.y_ / float(sprite_.getTexture()->getSize().y);

        if (mode_ == FILL_X)
        {
            scale_y = scale_x;
        }

        if (mode_ == FILL_Y)
        {
            scale_x = scale_y;
        }

        sprite_.setScale(scale_x, scale_y);
    }

    Vector2d Sprite::getScale()
    {
        return Vector2d(sprite_.getScale());
    }
}