#pragma once

#include "Text.h"
#include "Vector2d.h"
#include "Sprite.h"

class RenderTexture
{
public:
    Vector2d shape_;
    sf::RenderTexture render_texture_;
    
    RenderTexture(Vector2d shape):
        shape_(shape),
        render_texture_()
    {
        render_texture_.create(shape.x_, shape_.y_);
    };
    
    void create(const Vector2d &shape)
    {
        render_texture_.create(shape.x_, shape.y_);      
    }
 
    void draw(const Sprite &sprite)
    {
        render_texture_.draw(sprite.sprite_);
    }

    void draw(const Text &text)
    {
        render_texture_.draw(text.text_);
    }
    
    void display()
    {
        render_texture_.display();
    }

    Texture getTexture()
    {
        return Texture(render_texture_.getTexture());
    }

    Vector2d getSize()
    {
        return Vector2d(render_texture_.getSize());
    }

    void clear()
    {
        render_texture_.clear();
    }
};