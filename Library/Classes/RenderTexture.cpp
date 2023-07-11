#pragma once

#include "RenderTexture.hpp"

namespace SL
{
    RenderTexture::RenderTexture(Vector2d size)
    {
        create(size);
    };
        
    RenderTexture::RenderTexture(const RenderTexture &source)
    {
        create(source.getSize());
        draw(Sprite(source.getSize(), source.getTexture()));
    }


    RenderTexture& RenderTexture::operator=(const RenderTexture &source)
    {
        create(source.getSize());
        draw(Sprite(source.getSize(), source.getTexture()));

        return *this;
    }

    RenderTexture::RenderTexture(RenderTexture &&source)
    {
        create(source.getSize());
        draw(Sprite(source.getSize(), source.getTexture()));
    }


    RenderTexture& RenderTexture::operator=(RenderTexture &&source)
    {
        create(source.getSize());
        draw(Sprite(source.getSize(), source.getTexture()));

        return *this;
    }

    Texture RenderTexture::getTexture() const 
    {
        return Texture(render_texture_.getTexture());
    }

    Vector2d RenderTexture::getSize() const 
    {
        return Vector2d(render_texture_.getSize());
    }

    void RenderTexture::setSize(Vector2d size)
    {            
        Sprite sprite(size, getTexture());
    
        create(size);
        draw(sprite);
    }

    void RenderTexture::create(const Vector2d &size)
    {
        render_texture_.create((uint32_t)size.x_, (uint32_t)size.y_);      
    }

    void RenderTexture::draw(const Sprite &sprite)
    {
        render_texture_.draw(sprite.sprite_);
    }

    void RenderTexture::draw(const Text &text)
    {
        render_texture_.draw(text.text_);
    }
    
    void RenderTexture::display()
    {
        render_texture_.display();
    }

    void RenderTexture::clear(const Color &color = Color(0, 0, 0, 255))
    {
        render_texture_.clear(color.get_sf_color());
    }
}