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

    Button(point center, int width, int height, Widget *parent_widget, const Color &color = Colors::White, const char *text = "") : 
        Widget(center, width, height, parent_widget),
        color_(color)
        {
            for(int i = 0; text[i] != '\0' && i < 120; i++)
            {
                text_[i] = text[i];
            }
        };
    
    bool point_belonging(point point) override;
    void draw(Color *array, int app_width) override;
    void add(Widget *widget) override
    {
        child_widgets_.push_back(widget);
    }
};


void Button::draw(Color *array, int app_width)
{    
    point parent_start = {parent_widget_->center_.x - parent_widget_->width_ / 2, parent_widget_->center_.y - parent_widget_->height_ / 2};
    
    point start = {parent_start.x + center_.x - width_ / 2, parent_start.y + center_.y - height_ / 2};
    point end   = {parent_start.x + center_.x + width_ / 2, parent_start.y + center_.y + height_ / 2};

    for (int i = start.y; i < end.y; i++)
    {
        for (int j = start.x; j < end.x; j++)
        {
            array[i * app_width + j] = color_;
        }
    }
}

bool Button::point_belonging(point point)
{
    return abs(point.x - center_.x) < width_ / 2 && abs(point.y - center_.y) < height_ / 2;
}