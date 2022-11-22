#pragma once

#include "SFML/Graphics.hpp"
#include "Texture.h"
#include "tools.h"

class Image : public booba::Image
{

protected:
    sf::Image image_;

public:    
    Image ()
    {}
    
    ~Image ()
    {}
    Image(const char *path)
    {
        image_.loadFromFile(path);
    }

    Image(const Texture &texture)
    {
        image_ = texture.texture_.copyToImage();
    }

    Texture getTexture() const
    {
        Texture texture;
        texture.texture_.loadFromImage(image_);
        return texture;
    }

    uint32_t getH() override
    {
        return getSize().y_;
    }

    uint32_t getX() override
    {
        return getSize().x_;
    }

    Vector2d getSize() const
    {
        return Vector2d(image_.getSize());
    }

    uint32_t getPixel(int32_t x, int32_t y) override
    {
        return (uint32_t(image_.getPixel(x, y).r) << 24) + (uint32_t(image_.getPixel(x, y).g) << 16) + (uint32_t(image_.getPixel(x, y).b) << 8);
    }

    Color getPixel(Vector2d pos) const
    {
        return Color(image_.getPixel(pos.x_, pos.y_));
    }
    
    void putPixel(uint32_t x, uint32_t y, uint32_t color) override
    {        
        Color color_((uint8_t)(color >> 24), (color >> 16) & ((1 << 8) - 1), color >> 8 & ((1 << 8) - 1));
        setPixel(Vector2d(x, y), color_);
    }   

    void setPixel(Vector2d pos, const Color &color)
    {
        image_.setPixel(pos.x_, pos.y_, sf::Color::Black);
    }

    uint32_t& operator()(uint32_t, uint32_t) override 
    {
        return *(uint32_t *)this;
    }

    const uint32_t& operator()(uint32_t, uint32_t) const override 
    {
        return *(uint32_t *)this;
    }

    bool saveToFile(const char *filename)
    {
        return image_.saveToFile(filename);
    }
};