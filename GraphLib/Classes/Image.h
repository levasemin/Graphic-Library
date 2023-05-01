#pragma once

#include "SFML/Graphics.hpp"
#include "Texture.h"
#include "../Event/tools.h"
// #include "optionals.h"
#include "RenderTexture.h"

namespace SL
{
    class Image : public booba::Image
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

        size_t getH() override
        {
            return size_t(getSize().y_);
        }

        size_t getW() override
        {
            return size_t(getSize().x_);
        }

        Vector2d getSize() const
        {
            return Vector2d(image_.getSize());
        }

        void setSize(const Vector2d &size)
        {
            image_.create(uint32_t(size.x_), uint32_t(size.y_));
        }   
        
        uint32_t getPixel(size_t x, size_t y) override
        {
            Color color(image_.getPixel(uint32_t(x), uint32_t(y)));
            return Color::convert_color_uint(color);
        }

        Color getPixel(Vector2d pos) const
        {
            return Color(image_.getPixel(uint32_t(pos.x_), uint32_t(pos.y_)));
        }
        
        void setPixel(size_t x, size_t y, uint32_t color) override
        {        
            image_changed = true;
            setPixel(Vector2d(float(x), float(y)), Color::convert_uint_color(color));
        }   

        void setPixel(Vector2d pos, const Color &color)
        {
            image_.setPixel(uint32_t(pos.x_), uint32_t(pos.y_), color.get_sf_color());
        }

        booba::Picture getPicture(size_t x, size_t y, size_t h, size_t w) override
        {
            return booba::Picture(x, y, w, h, this);
        }

        void setPicture(booba::Picture &&pic) override
        {
            // sf::Image image;
            // image.create(pic.getW(), pic.getH(), sf::Color(0, 0, 255, 255));
        
            // RenderTexture render_texture(Vector2d(image_.getSize().x, image_.getSize().y));
            // Sprite main_sprite(Vector2d(image_.getSize().x, image_.getSize().y), getTexture());
            
            // Texture texture;
            // texture.texture_.loadFromImage(image);

            // Sprite pic_sprite(Vector2d(pic.getW(), pic.getH()), texture);
            // pic_sprite.setPosition(Vector2d(pic.getX(), pic.getY()));
            
            // render_texture.clear();
            // render_texture.draw(main_sprite);
            // render_texture.draw(pic_sprite);
            // render_texture.display();
            
            // image_ = render_texture.render_texture_.getTexture().copyToImage();
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