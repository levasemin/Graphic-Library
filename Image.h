#pragma once

#include "SFML/Graphics.hpp"
#include "Texture.h"
#include "tools.h"

class Image : public booba::Image
{
public:    
    sf::Image image_;

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

    Image (const Vector2d &shape)
    {
        image_.create(shape.x_, shape.y_);
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
    
    static Color convert_uint_color(uint32_t color)
    {
        return Color((uint8_t)(color >> 24), (uint8_t)(color >> 16), (uint8_t)(color >> 8));
    }

    static uint32_t convert_color_uint(const Color &color)
    {
        return ((uint32_t)color.r_ << (uint32_t)24) + ((uint32_t)color.g_ << (uint32_t)16) + ((uint32_t)color.b_ << (uint32_t)8);
    }

    uint32_t getPixel(int32_t x, int32_t y) override
    {
        Color color(image_.getPixel(x, y));
        return convert_color_uint(color);
    }

    Color getPixel(Vector2d pos) const
    {
        return Color(image_.getPixel(pos.x_, pos.y_));
    }
    
    void putPixel(uint32_t x, uint32_t y, uint32_t color) override
    {        
        setPixel(Vector2d(x, y), convert_uint_color(color));
    }   

    void setPixel(Vector2d pos, const Color &color)
    {
        image_.setPixel(pos.x_, pos.y_, color.get_sf_color());
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