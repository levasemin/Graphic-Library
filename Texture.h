#pragma once

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
        field_ = new Color[(int)(shape.x_ * shape.y_)]();
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

    Texture (Vector2d shape, const Color &color) : Texture(shape)
    {
        for (int y = 0; y < shape_.y_; y++)
        {
            for (int x = 0; x < shape_.x_; x++)
            {
                field_[y * (int)shape_.x_ + x] = color;
            }
        }
    };
    
    Color &operator [] (int index)
    {
        return field_[index];
    }
};