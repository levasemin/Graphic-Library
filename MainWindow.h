#pragma once

#include "Widget.h"
#include "Color.h"

class MainWindow : public Widget
{
public:
    point center_;
    int width_;
    int height_;
    Color color_;

    Color *field_;
    MainWindow *parent_;
    std::vector<MainWindow *> children_ = {};

    MainWindow(int width, int height, point center = {-1, -1}, Color color = Colors::White, int style = sf::Style::Default, MainWindow *parent = nullptr):
        Widget{},
        width_(width),
        height_(height),
        color_(color),
        center_(center),
        parent_(parent)
        {
            if (center.x == -1 && center.y == -1)
            {
                center_ = {width / 2, height / 2};
            }

            if (parent == nullptr)
            {
                field_ = (Color *)calloc(width * height, sizeof(Color));
            }
            
            else
            {
                field_ = parent->field_;
            }
        };

    virtual bool point_belonging(point point) const
    {
        return point.x < width_ && point.y < height_;
    }

    virtual void draw(int app_width)
    {    
        for (int i = 0; i < height_; i++)
        {
            for (int j = 0; j < width_; j++)
            {
                field_[i * width_ + j] = color_;
            }
        }

        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->draw(width_);
        }
    }

    virtual void add(MainWindow *window)
    {
        window->parent_ = this;
        children_.push_back(window);

        free(window->field_);
        window->field_ = field_;

        set_field(window);
    }

    void set_field(MainWindow *window)
    {
        for (int i = 0; i < window->children_.size(); i++)
        {
            if (window->children_[i]->field_ == nullptr)
            {
                printf("EHE\n");
            }
            
            window->children_[i]->field_ = window->field_;

            set_field(window->children_[i]);
        }
    }
};