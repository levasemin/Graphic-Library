#include "Color.h"
#include "Window.h"
#include "Widget.h"

class Container : public Widget
{
public:

    Color color_;

    Container(point center, int width, int height, Widget *parent_widget, const Color &color = Colors::Red, const std::vector<Widget *> &widgets = {}): 
        Widget(center, width, height, parent_widget),
        color_(color)
        {};

    void draw(Color *array, int app_width) override;
    bool point_belonging(point point) override;
    void add(Widget *widget) override
    {
        child_widgets_.push_back(widget);
    }
};

void Container::draw(Color *array, int app_width)
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

    if (child_widgets_.size() == 0)
    {
        return;
    }

    for (int i = 0; i < child_widgets_.size(); i++)
    {
        child_widgets_[i]->draw(array, app_width);
    }
}


bool Container::point_belonging(point point)
{
    return abs(point.x - center_.x) < width_ / 2 && abs(point.y - center_.y) < height_ / 2;
}


