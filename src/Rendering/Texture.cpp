#include "Texture.hpp"
#include "Image.hpp"

namespace SL
{        
    Texture::Texture(const char *path):
        texture_()
    {
        loadFromFile(path);
    };
    
    Texture::Texture (const Color &color):
        texture_()
    {
        sf::Image image;
        image.create(100, 100, color.get_sf_color());
        texture_.loadFromImage(image);
    }

    Texture::Texture (const sf::Texture &texture):
        texture_(texture)
    {
    }
    
    bool Texture::loadFromFile(const char *path)
    {
        return texture_.loadFromFile(path);
    }

    Vector2d Texture::getSize() const
    {
        return Vector2d(texture_.getSize());
    }

    Image Texture::copyToImage()
    {
        return Image(texture_.copyToImage());
    }    
}