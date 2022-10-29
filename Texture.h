#include "Vector2d.h"
#include "Color.h"

class Texture
{
public:
    Color *field_ = nullptr;
    Vector2d shape_;

    Texture(Vector2d shape):
        shape_(shape)
    {
        field_ = new Color[shape.x_ * shape.y_];
    }

    Texture(const char *path) 
    {
        sf::Image image;
        image.loadFromFile(path);
        Texture(Vector2d(image.getSize().x, image.getSize().y)); 

        for (int y = 0; y < shape_.y_; y++)
        {
            for (int x = 0; x < shape_.x_; x++)
            {
                field_[y * (int)shape_.y_ + x] = Color(image.getPixel(x, y));
            }
        }
    };

    Texture (const Color &color)
    {
        for (int y = 0; y < shape_.y_; y++)
        {
            for (int x = 0; x < shape_.x_; x++)
            {
                field_[y * (int)shape_.y_ + x] = color;
            }
        }
    };
};