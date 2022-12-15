#pragma once

#include "SFML/Graphics.hpp"
#include "Texture.h"
#include "tools.h"

namespace SL
{
    class Image : public booba::Image
    {
    public:    
        sf::Image image_;

        Image () : 
            image_()
        {}

        ~Image() override {}
        
        Image(const std::string &path):
            image_()
        {
            loadFromFile(path);
        }

        Image(const Texture &texture):
            image_()
        {
            image_ = texture.texture_.copyToImage();
        }

        Image (const Vector2d &shape):
            image_()
        {
            image_.create(uint32_t(shape.x_), uint32_t(shape.y_));
        }
        
        void saveToFile(const std::string &path)
        {
            image_.saveToFile(path);
        }

        void loadFromFile(const std::string &path)
        {
            image_.loadFromFile(path);
        }

        Texture getTexture() const
        {
            Texture texture;
            texture.texture_.loadFromImage(image_);
            return texture;
        }

        uint32_t getH() override
        {
            return uint32_t(getSize().y_);
        }

        uint32_t getX() override
        {
            return uint32_t(getSize().x_);
        }

        Vector2d getSize() const
        {
            return Vector2d(image_.getSize());
        }

        void setSize(const Vector2d &size)
        {
            image_.create(uint32_t(size.x_), uint32_t(size.y_));
        }   

        uint32_t getPixel(int32_t x, int32_t y) override
        {
            Color color(image_.getPixel(x, y));
            return Color::convert_color_uint(color);
        }

        Color getPixel(Vector2d pos) const
        {
            return Color(image_.getPixel(uint32_t(pos.x_), uint32_t(pos.y_)));
        }
        
        void putPixel(uint32_t x, uint32_t y, uint32_t color) override
        {        
            setPixel(Vector2d(float(x), float(y)), Color::convert_uint_color(color));
        }   

        void setPixel(Vector2d pos, const Color &color)
        {
            image_.setPixel(uint32_t(pos.x_), uint32_t(pos.y_), color.get_sf_color());
        }

        uint32_t& operator()(uint32_t, uint32_t) override 
        {
            uint32_t *smth = new uint32_t;
            return *smth;
        }

        const uint32_t& operator()(uint32_t, uint32_t) const override 
        {
            uint32_t *smth = new uint32_t;
            return *smth;
        }

        bool saveToFile(const char *filename)
        {
            return image_.saveToFile(filename);
        }
    };
}