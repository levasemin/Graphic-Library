#pragma once

#include "Widget.h"
#include "VirtualWindow.h"
#include "Color.h"
#include "Vector2d.h"

class ScrollVirtualWindow : public VirtualWindow
{
public:
    ScrollVirtualWindow(Vector2d shape, Vector2d center = {-1, -1}, Color color = Colors::White, VirtualWindow *parent = nullptr, std::vector<VirtualWindow *> children = {}):
        VirtualWindow(shape, center, color, parent, children)
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

   
    void ScrollEvent (Vector2d point, double offset) override
    {
        displayed_children_.clear();
        
        this->set_offset(Vector2d(0, offset));
        
        for (int i = 0; i < children_.size(); i++)
        {            
            if (children_[i]->center_.x_ + children_[i]->shape_.x_ / 2 > center_.x_ - shape_.x_ / 2 &&
                children_[i]->center_.x_ - children_[i]->shape_.x_ / 2 < center_.x_ + shape_.x_ / 2)
            {
                displayed_children_.push_back(children_[i]);
            }
        }
    }
};