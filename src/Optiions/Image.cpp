#include "Image.hpp"
#include "Texture.hpp"

namespace SL
{
    Image::Image () : 
        image_()
    {}
    
    Image::Image(const std::string &path):
        image_()
    {
        loadFromFile(path);
    }

    Image::Image(const Texture &texture):
        image_()
    {
        image_ = texture.texture_.copyToImage();
    }

    Image::Image (const Vector2d &shape, const Color &color = Color(uint8_t(0), uint8_t(0), uint8_t(0))):
        image_()
    {
        image_.create(uint32_t(shape.x_), uint32_t(shape.y_), color.get_sf_color());
    }
    
    Image::Image(const sf::Image &image): image_(image)
    {}

    void Image::saveToFile(const std::string &path)
    {
        image_.saveToFile(path);
    }

    void Image::loadFromFile(const std::string &path)
    {
        image_.loadFromFile(path);
    }

    Texture Image::getTexture() const
    {
        Texture texture;
        texture.texture_.loadFromImage(image_);
        return texture;
    }

    Vector2d Image::getSize() const
    {
        return Vector2d(image_.getSize());
    }

    void Image::setSize(const Vector2d &size)
    {
        image_.create(uint32_t(size.x_), uint32_t(size.y_));
    }   

    Color Image::getPixel(Vector2d pos) const
    {
        return Color(image_.getPixel(uint32_t(pos.x_), uint32_t(pos.y_)));
    }

    void Image::setPixel(Vector2d pos, const Color &color)
    {
        image_.setPixel(uint32_t(pos.x_), uint32_t(pos.y_), color.get_sf_color());
    }

    void Image::create(Vector2d shape, const Color &color = Color(0, 0, 0, 255))
    {
        image_.create(uint32_t(shape.x_), uint32_t(shape.y_), color.get_sf_color());
    }

    bool Image::saveToFile(const char *filename)
    {
        return image_.saveToFile(filename);
    }

    void Image::copy(const Image &source, Vector2d place, Vector2d source_start, Vector2d source_end, bool applyAlpha)
    {
        if (source_start.x_ == -1 && source_start.y_ == -1)
        {
            source_start = Vector2d(0, 0);
        }

        if (source_end.x_ == -1 && source_end.y_ == -1)
        {
            source_end = source.getSize();
        }

        image_.copy(source.image_, place.x_, place.y_, sf::IntRect(source_start.x_, source_start.y_, source_end.x_, source_end.y_), applyAlpha);
    }

}