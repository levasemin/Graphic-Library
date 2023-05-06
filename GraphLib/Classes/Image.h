#pragma once

#include "SFML/Graphics.hpp"
#include "Texture.h"
#include "RenderTexture.h"
#include <SFML/Config.hpp>

namespace SL
{
    class Image
    {
    public:    
        sf::Image image_;

        bool image_changed = true;

        Image () : 
            image_()
        {}
        
        virtual ~Image() {};

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

        Image (const Vector2d &shape, const Color &color = Color(uint8_t(0), uint8_t(0), uint8_t(0))):
            image_()
        {
            image_.create(uint32_t(shape.x_), uint32_t(shape.y_), color.get_sf_color());
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

        Vector2d getSize() const
        {
            return Vector2d(image_.getSize());
        }

        void setSize(const Vector2d &size)
        {
            image_.create(uint32_t(size.x_), uint32_t(size.y_));
        }   

        Color getPixel(Vector2d pos) const
        {
            return Color(image_.getPixel(uint32_t(pos.x_), uint32_t(pos.y_)));
        }

        void setPixel(Vector2d pos, const Color &color)
        {
            image_.setPixel(uint32_t(pos.x_), uint32_t(pos.y_), color.get_sf_color());
        }

        void create(Vector2d shape, const Color &color = Color(0, 0, 0, 255))
        {
            image_.create(uint32_t(shape.x_), uint32_t(shape.y_), color.get_sf_color());
        }

        bool saveToFile(const char *filename)
        {
            return image_.saveToFile(filename);
        }
    };
}