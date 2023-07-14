#pragma once

#include "SFML/Graphics.hpp"
#include "Texture.hpp"
#include "RenderTexture.hpp"
#include <SFML/Config.hpp>

namespace SL
{
    class Image
    {
    private:
        sf::Image image_;
        
    public:    

        Image ();
        virtual ~Image() {};

        Image(const std::string &path);

        Image(const Texture &texture);

        Image (const Vector2d &shape, const Color &color);
        
        void saveToFile(const std::string &path);

        void loadFromFile(const std::string &path);

        Texture getTexture() const;

        Vector2d getSize() const;

        void setSize(const Vector2d &size);   

        Color getPixel(Vector2d pos) const;

        void setPixel(Vector2d pos, const Color &color);

        void create(Vector2d shape, const Color &color);

        bool saveToFile(const char *filename);
    };
}