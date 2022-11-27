#pragma once

#include "Texture.h"

const int FILL   = 0;
const int FILL_X = 1;
const int FILL_Y = 2;
const int CROP   = 3;

class Sprite
{

public:
    Vector2d shape_;
    sf::Sprite sprite_;
    Texture texture_;

    Sprite(Vector2d shape, const Texture &texture, int mode = FILL):
        mode_(mode),
        shape_(shape),
        texture_(texture)
    {
        setTexture(texture_);
    };

    Sprite(sf::Sprite sprite):
        mode_(0),
        sprite_(sprite),
        texture_(*sprite.getTexture()),
        shape_(sprite.getTextureRect().width   * sprite.getScale().x,
               sprite_.getTextureRect().height * sprite.getScale().y)
    {
    }

    void setTextureRect(Vector2d start, Vector2d end)
    {
        sprite_.setTextureRect(sf::IntRect(start.x_, start.y_, end.x_, end.y_));
    }

    void set_shape(Vector2d shape, bool with_rescale = true)
    {
        shape_ = shape;
        
        if (with_rescale)
        {
            rescale();
        }
    }
    
    Texture getTexture()
    {
        return texture_;
    }

    void setTexture(const Texture &texture, bool resetRect = true)
    {
        texture_ = texture;
        sprite_.setTexture(texture_.texture_, resetRect);
        
        if (resetRect) 
        {
            rescale();
        }
    }

    void setPosition(Vector2d position)
    {
        sprite_.setPosition(sf::Vector2f(position.x_, position.y_));
    }

    void rescale()
    {
        float scale_x = shape_.x_ / sprite_.getTexture()->getSize().x;
        float scale_y = shape_.y_ / sprite_.getTexture()->getSize().y;

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

    Vector2d getScale()
    {
        return Vector2d(sprite_.getScale());
    }

private:
    int mode_;
};