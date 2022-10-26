#pragma once

#include "Color.h"
#include "Window.h"
#include "Widget.h"
#include "Vector2d.h"

class Container : public MainWindow
{
public:

    Color color_;

    Container(Vector2d shape, Vector2d center, const Color &color = Colors::Red, MainWindow *parent = nullptr, const std::vector<Widget *> &widgets = {}): 
        MainWindow(shape, center, color, sf::Style::Default, parent),
        color_(color)
        {};

    void draw(int app_width) override;
    bool point_belonging(Vector2d point) const override;
};

void Container::draw(int app_width)
{
    Vector2d start = center_ - shape_ / 2;
    Vector2d end   = center_ + shape_ / 2;

    for (int i = start.y_; i < end.y_; i++)
    {
        for (int j = start.x_; j < end.x_; j++)
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


bool Container::point_belonging(Vector2d point) const
{
    return abs(point.x_ - center_.x_) < shape_.x_ / 2 && abs(point.y_ - center_.y_) < shape_.y_ / 2;
}


