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
        render_texture_.create(720, 720);
    };

    void draw(Sprite sprite)
    {
        render_texture_.draw(sprite.sprite_);
    }

    void draw(Text text)
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

    void clear()
    {
        render_texture_.clear();
    }
};