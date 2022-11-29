#pragma once

#include "RenderTexture.h"
#include "Image.h"

class Circle : public Image
{
protected:
    int radius_ = 0;
    Color color_;
     
public:
    Circle(int radius, Color color = Color::Black): Image(Vector2d(radius * 2, radius * 2)),
        radius_(radius),
        color_(color)
    {
        fill_circle();
    }

    Circle(int radius, uint32_t color): Circle(radius, Color::convert_uint_color(color))
    {}

    void fill_circle()
    {
        for (int y = 0; y < radius_ * 2; y++)
        {
            for (int x = 0; x < radius_ * 2; x++)
            {
                Color point_color((uint8_t)1, 0, 1);

                if (pow(x - radius_, 2) + pow(y - radius_, 2) <= pow(radius_, 2))
                {
                    point_color = color_;
                    
                }

                setPixel(Vector2d(x, y), point_color);
            }
        }
    }

    void set_radius(int radius)
    {
        radius_ = radius;
        setSize(Vector2d(radius * 2, radius * 2));
        
        fill_circle();
    }

    int get_radius()
    {
        return radius_;
    }

    void set_color(const Color &color)
    {
        color_ = color;
        fill_circle();
    }

    void draw_on_image(booba::Image *image, Vector2d center)
    {
        for (int y = 0; y < radius_ * 2; y++)
        {
            for (int x = 0; x < radius_ * 2; x++)
            {
                if (getPixel(Vector2d((int)x, (int)y)) == color_)
                {
                    image->putPixel(uint32_t((int)center.x_ + x - radius_), (uint32_t)((int)center.y_ + y - radius_), convert_color_uint(color_));
                }
            }
        }
    }
};