#pragma once

#include "Color.h"
#include "Window.h"
#include "Widget.h"

class Container : public MainWindow
{
public:

    Color color_;

    Container(point center, int width, int height, const Color &color = Colors::Red, MainWindow *parent = nullptr, const std::vector<Widget *> &widgets = {}): 
        MainWindow(width, height, center, color, sf::Style::Default, parent),
        color_(color),
        center_(center)
        {};

    point center_;
    void draw(int app_width) override;
    bool point_belonging(point point) const override;
};

void Container::draw(int app_width)
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

    if (children_.size() == 0)
    {
        return;
    }

    for (int i = 0; i < children_.size(); i++)
    {
        children_[i]->draw(app_width);
    }
}


bool Container::point_belonging(point point) const
{
    return abs(point.x - center_.x) < width_ / 2 && abs(point.y - center_.y) < height_ / 2;
}


