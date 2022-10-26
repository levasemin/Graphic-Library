#pragma once

#include "Widget.h"
#include "Color.h"
#include "Vector2d.h"

class MainWindow : public Widget
{
public:
    Vector2d center_;
    Vector2d shape_;
    Color color_;

    Color *field_;
    MainWindow *parent_;
    std::vector<MainWindow *> children_ = {};

    MainWindow(Vector2d shape, Vector2d center = {-1, -1}, Color color = Colors::White, int style = sf::Style::Default, MainWindow *parent = nullptr):
        Widget{},
        shape_(shape),
        color_(color),
        center_(center),
        parent_(parent)
        {
            if (center.x_ == -1 && center.y_ == -1)
            {
                center_ = shape_ / 2;
            }

            if (parent == nullptr)
            {
                field_ = (Color *)calloc(shape.x_ * shape.y_, sizeof(Color));
            }
            
            else
            {
                field_ = parent->field_;
            }
        };

    void set_field(MainWindow *window, Vector2d offset)
    {
        for (int i = 0; i < window->children_.size(); i++)
        {
            window->children_[i]->center_ += offset;
            window->children_[i]->field_ = window->field_;

            set_field(window->children_[i], offset);
        }
    }

    void ClickLeftEvent     (Vector2d point)   override {};
    void MissClickLeftEvent (Vector2d point)   override {};
    void ClickRightEvent    (Vector2d point)   override {};
    void MissClickRightEvent(Vector2d point)   override {};
    void PressKeyEvent      (int key)       override {};
    void ScrollEvent        (double offset) override {};
    void Close              ()              override {};

    virtual bool point_belonging(Vector2d point) const
    {
        return point.x_ < shape_.x_ && point.y_ < shape_.y_;
    }

    virtual void draw(int app_width)
    {    
        for (int i = 0; i < shape_.y_; i++)
        {
            for (int j = 0; j < shape_.x_; j++)
            {
                field_[i * (int)shape_.x_ + j] = color_;
            }
        }

        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->draw(shape_.x_);
        }
    }

    virtual void add(MainWindow *window)
    {
        window->parent_ = this;
        children_.push_back(window);

        free(window->field_);
        window->field_ = field_;
        
        Vector2d offset = center_ - shape_ / 2;
        window->center_ +=  offset;
        set_field(window, offset);
    }
};