#pragma once

#include "SFML/Graphics.hpp"
#include "../Rendering/RenderTexture.hpp"
#include <SFML/Config.hpp>

namespace SL
{
    class Texture;
    
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
    };
}