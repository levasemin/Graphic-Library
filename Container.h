#include "Color.h"
#include "Window.h"
#include "Widget.h"

class Container : public Widget
{
public:

    Color color_;
    int border_;

    Container(point center, int width, int height, const std::vector<Widget *> &widgets, const Color &color = Colors::Red, int border = 0): 
        Widget(center, width, height),
        widgets_(widgets),
        color_(color),
        border_(border)
        {};

    std::vector<Widget *> widgets_;
    void draw(Window *) override;
    void draw(Window *, point center);
    bool point_belonging(point point) override;
};

void Container::draw(Window *window, point center)
{
    sf::RectangleShape field_(sf::Vector2f(width_, height_)); 
    field_.setPosition(center.x - width_ / 2, center.y - height_ / 2);
    field_.setFillColor(color_.get_sf_color());        

    window->window_.draw(field_);

    if (widgets_.size() == 0)
    {
        return;
    }

    point new_center = {center.x, center.y - height_ / 2 + border_};

    for (int i = 0; i < widgets_.size(); i++)
    {
        new_center = {new_center.x, new_center.y + widgets_[i]->height_ / 2};

        widgets_[i]->draw(window, new_center);

        new_center = {new_center.x, new_center.y + widgets_[i]->height_ / 2 + border_};
    }
}

void Container::draw(Window *window)
{
    draw(window, center_);
}

bool Container::point_belonging(point point)
{
    return abs(point.x - center_.x) < width_ / 2 && abs(point.y - center_.y) < height_ / 2;
}


