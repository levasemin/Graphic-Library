#pragma once

#include "Widget.h"
#include "Color.h"

class MainWindow : public Widget
{
public:
    Color color_;

    MainWindow(int width, int height, int style = sf::Style::Default, Color color = Colors::White) :  
        Widget({width / 2, height / 2}, width, height, nullptr),
        color_(color)
        {
            field_ = (Color *)calloc(width * height, sizeof(Color));
        };

    Color *field_;

    bool point_belonging(point point) override
    {
        return abs(point.x - center_.x) < width_ / 2 && abs(point.y - center_.y) < height_ / 2;
    }

    void draw(Color *field, int app_width) override
    {    
        point start = {center_.x - width_ / 2, center_.y - height_ / 2};
        point end   = {center_.x + width_ / 2, center_.y + height_ / 2};

        for (int i = start.y; i < end.y; i++)
        {
            for (int j = start.x; j < end.x; j++)
            {
                field_[i * width_ + j] = color_;
            }
        }

        for (int i = 0; i < child_widgets_.size(); i++)
        {
            child_widgets_[i]->draw(field_, width_);
        }
    }

    void add(Widget *widget) override
    {
        child_widgets_.push_back(widget);
    }
};