#pragma once

#include "Vector2d.h"
#include "Color.h"

const int FILL   = 0;
const int FILL_X = 1;
const int FILL_Y = 2;
const int CROP   = 3;

class Texture
{
    
public:

    int mode_;

    Color *field_ = nullptr;
    Vector2d shape_;
    
    Texture(Vector2d shape , int mode = FILL_Y):
        mode_(mode),
        shape_(shape)
    {
        field_ = new Color[(int)(shape.x_ * shape.y_)]();
    }

    Texture(Vector2d shape, const char *path) : Texture(shape) 
    {
        sf::Image image;
        image.loadFromFile(path);

        Vector2d start(0, 0), end(shape_);
    
        double coeff_x = image.getSize().x / shape_.x_;
        double coeff_y = image.getSize().y / shape_.y_;

        if (mode_ == FILL_X)
        {
            coeff_y = coeff_x;

            start.x_ = 0;
            start.y_ = (shape_.y_ - image.getSize().y / coeff_x) / 2;
            start.y_ = start.y_ < 0 ? 0 : start.y_;
            
            end.x_   = shape_.x_;  
            end.y_   = shape_.y_ - start.y_ - 10; 

            start.print_value();
            end.print_value();
        }   

        if (mode_ == FILL_Y)
        {
            coeff_x = coeff_y;

            start.y_ = 0;
            start.x_ = (shape_.x_ - image.getSize().x / coeff_y) / 2;
            start.x_ = start.x_ < 0 ? 0 : start.x_; 

            end.y_   = shape_.y_;  
            end.x_   = shape_.x_ - start.x_; 
        }

        for (int y = 0; y < shape_.y_; y++)
        {
            for (int x = 0; x < shape_.x_; x++)
            {
                Color avarage_color(0, 0, 0);

                if (y >= start.y_ && x >= start.x_ && y <= end.y_ && x <= end.x_)
                {
                    for (int i = (y - start.y_) * coeff_y; i < (y - start.y_ + 1) * coeff_y; i++)
                    {
                        for (int j = (x - start.x_) * coeff_x; j < (x - start.x_ + 1) * coeff_x; j++)
                        {                            
                            avarage_color += Color(image.getPixel(j, i));
                        }
                    }
                }

                avarage_color /= coeff_y * coeff_x;
                avarage_color.claim();
                field_[y * (int)shape_.x_ + x] = avarage_color;
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