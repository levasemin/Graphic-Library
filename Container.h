#include "Color.h"
#include "Window.h"
#include "Widget.h"

class Container : public Widget
{
public:

    Color color_;

    Container(point center, int width, int height, Widget *parent_widget, const std::vector<Widget *> &widgets, const Color &color = Colors::Red): 
        Widget(center, width, height, parent_widget),
        widgets_(widgets),
        color_(color)
        {};

    std::vector<Widget *> widgets_;
    void draw(Color *array, int app_width) override;
    bool point_belonging(point point) override;
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

    if (widgets_.size() == 0)
    {
        return;
    }

    for (int i = 0; i < widgets_.size(); i++)
    {
        widgets_[i]->draw(array, app_width);
    }
}


bool Container::point_belonging(point point)
{
    return abs(point.x - center_.x) < width_ / 2 && abs(point.y - center_.y) < height_ / 2;
}


