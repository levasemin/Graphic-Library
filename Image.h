#pragma once

#include "SFML/Graphics.hpp"
#include "Texture.h"
#include "tools.h"

class Image : public booba::Image
{
    sf::Image image_;

public:
    
    protected:
        virtual ~Image() = 0;
    
    Image ()
    {}


    uint32_t getH() override
    {
        return getSize().y_;
    }

    uint32_t getX() override
    {
        return getSize().x_;
    }

    uint32_t getPixel(int32_t x, int32_t y) override
    {
        return (uint32_t(image_.getPixel(x, y).r) << 24) + (uint32_t(image_.getPixel(x, y).g) << 16) + (uint32_t(image_.getPixel(x, y).b) << 8);
    }

    Color getPixel(Vector2d pos)
    {
        return Color(image_.getPixel(pos.x_, pos.y_));
    }
    
    virtual void putPixel(uint32_t x, uint32_t y, uint32_t color)
    {
        realImage_.setPixel(width, height, {color.red_, color.green_, color.blue_});
    }   

    virtual uint32_t& operator()(uint32_t x, uint32_t y) = 0;
    virtual const uint32_t& operator()(uint32_t x, uint32_t y) const = 0;

    Image(const char *path)
    {
        image_.loadFromFile(path);
    }

    Image(const Texture &texture)
    {
        image_ = texture.texture_.copyToImage();
    }

    Vector2d getSize()
    {
        return Vector2d(image_.getSize());
    }

    Texture getTexture()
    {
        Texture texture;
        texture.texture_.loadFromImage(image_);
        return texture;
    }

    friend class Texture;
};