#pragma once

#include "Color.h"
#include "Widget.h"
#include "Handlers.h"
#include "math.h"

class Button : public Widget
{
public:
    char text_[120];
    Color color_;

    Button(point center, int width, int height, const Color &color = Colors::White, const char *text = "") : 
        Widget(center, width, height),
        color_(color)
        {
            for(int i = 0; text[i] != '\0' && i < 120; i++)
            {
                text_[i] = text[i];
            }
        };
    
    bool point_belonging(point point) override;
    void draw(Window *window) override;
    void draw(Window *window, point center) override;
};

void Button::draw(Window *window, point center)
{    
    sf::RectangleShape field_(sf::Vector2f(width_, height_)); 
    field_.setPosition(center.x - width_ / 2, center.y - height_ / 2);
    field_.setFillColor(color_.get_sf_color());        

    window->window_.draw(field_);
}

void Button::draw(Window *window)
{
    draw(window, center_);
}


bool Button::point_belonging(point point)
{
    return abs(point.x - center_.x) < width_ / 2 && abs(point.y - center_.y) < height_ / 2;
}