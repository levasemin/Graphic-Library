#pragma once

#include "Color.h"
#include "Widget.h"
#include "MainWindow.h"
#include "Handlers.h"
#include "math.h"

class Button : public MainWindow
{
public:
    char text_[120];
    Color color_;

    Button(point center, int width, int height, const Color &color = Colors::White, const char *text = "", MainWindow *parent = nullptr) : 
        MainWindow(width, height, center, color, sf::Style::Default, parent),
        color_(color)
        {
            for(int i = 0; text[i] != '\0' && i < 120; i++)
            {
                text_[i] = text[i];
            }
        };
    
    bool point_belonging(point point) const override;
    void draw(int app_width) override;
};


void Button::draw(int app_width)
{    
    point parent_start = {parent_->center_.x - parent_->width_ / 2, parent_->center_.y - parent_->height_ / 2};
    
    point start = {parent_start.x + center_.x - width_ / 2, parent_start.y + center_.y - height_ / 2};
    point end   = {parent_start.x + center_.x + width_ / 2, parent_start.y + center_.y + height_ / 2};

    for (int i = start.y; i < end.y; i++)
    {
        for (int j = start.x; j < end.x; j++)
        {
            field_[i * app_width + j] = color_;
        }
    }
}

bool Button::point_belonging(point point) const 
{
    return abs(point.x - center_.x - parent_->center_.x + parent_->width_ / 2) < width_ / 2 && abs(point.y - center_.y - parent_->center_.y + parent_->height_ / 2) < height_ / 2;
}