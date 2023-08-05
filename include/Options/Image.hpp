#pragma once

#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>

#include "RenderTexture.hpp"

namespace SL
{
    class Texture;
    
    class Image
    {   
    public:    

        Image ();
        virtual ~Image() {};

        Image(const std::string &path);

        Image(const Texture &texture);

        Image (const Vector2d &shape, const Color &color);

        Image(const sf::Image &image);
                
        void saveToFile(const std::string &path);

        void loadFromFile(const std::string &path);

        Texture getTexture() const;

        Vector2d getSize() const;

        void setSize(const Vector2d &size);   

        Color getPixel(Vector2d pos) const;

        void setPixel(Vector2d pos, const Color &color);

        void create(Vector2d shape, const Color &color);

        bool saveToFile(const char *filename);

        void copy(const Image &source, Vector2d place, Vector2d source_start = Vector2d(-1, -1), Vector2d source_end = Vector2d(-1, -1), bool applyAlpha = false);
    private:
        sf::Image image_;
    };
}