#pragma once

#include "Widget.h"
#include "Color.h"
#include "Vector2d.h"

class VirtualWindow : public Widget
{
public:
    Vector2d center_;
    Vector2d shape_;
    Color color_;

    Color *field_;
    VirtualWindow *parent_;
    std::vector<VirtualWindow *> children_ = {};
    std::vector<VirtualWindow *> displayed_children_ = {};

    VirtualWindow(Vector2d shape, Vector2d center = {-1, -1}, Color color = Colors::White, VirtualWindow *parent = nullptr, std::vector<VirtualWindow *> children = {}):
        Widget{},
        shape_(shape),
        color_(color),
        center_(center),
        parent_(parent),
        children_(children),
        displayed_children_()
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

            for (int i = 0; i < children_.size(); i++)
            {
                add(children_[i]);
            }
        };

    
    virtual void set_offset(Vector2d offset)
    {
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->center_ += offset;

            children_[i]->set_offset(offset);
        }
    }

    virtual void set_field()
    {
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->field_ = field_;

            children_[i]->set_field();
        }
    }

    void ClickLeftEvent     (Vector2d point)   override {};
    void MissClickLeftEvent (Vector2d point)   override {};
    void ReleasedLeftEvent  (Vector2d point)   override {};
    void ClickRightEvent    (Vector2d point)   override {};
    void MissClickRightEvent(Vector2d point)   override {};
    void ReleasedRightEvent (Vector2d point)   override {};
    void PressKeyEvent      (int key)       override {};
    void ScrollEvent        (Vector2d point, double offset) override{}
    void MoveMouse          (Vector2d point)   override {};

    void Close() override {};

    virtual bool point_belonging(Vector2d point) const
    {
        return abs(point.x_ - center_.x_) < shape_.x_ / 2 && abs(point.y_ - center_.y_) < shape_.y_ / 2;
    }

    virtual void draw(int app_width)
    {  
        Vector2d start = center_ - shape_ / 2;
        Vector2d end   = center_ + shape_ / 2;
        
        Vector2d down_limit  = parent_ != nullptr ? parent_->center_ - parent_->shape_ / 2 : Vector2d(0, 0);
        Vector2d hight_limit = parent_ != nullptr ? parent_->center_ + parent_->shape_ / 2 : Vector2d(shape_.x_, shape_.y_);

        start.x_ = start.x_ < down_limit.x_ ? down_limit.x_ : start.x_;
        start.y_ = start.y_ < down_limit.y_ ? down_limit.y_ : start.y_;

        end.x_ = end.x_ > hight_limit.x_ ? hight_limit.x_ : end.x_;
        end.y_ = end.y_ > hight_limit.y_ ? hight_limit.y_ : end.y_;
        
        for (int i = start.y_; i < end.y_; i++)
        {
            for (int j = start.x_; j < end.x_; j++)
            {
                field_[i * app_width + j] = color_;
            }
        }

        for (int i = 0; i < displayed_children_.size(); i++)
        {
            displayed_children_[i]->draw(app_width);
        }
    }

    virtual void add(VirtualWindow *window)
    {
        window->parent_ = this;
        children_.push_back(window);

        free(window->field_);
        window->field_ = field_;
        
        Vector2d offset = center_ - shape_ / 2;
        window->center_ +=  offset;

        window->set_offset(offset);
        window->set_field();

        if (window->center_.x_ + window->shape_.x_ / 2 > center_.x_ - shape_.x_ / 2 &&
        window->center_.x_ - window->shape_.x_ / 2 < center_.x_ + shape_.x_ / 2)
        {
            displayed_children_.push_back(window);
        }
    }
};