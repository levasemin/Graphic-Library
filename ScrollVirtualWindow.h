#pragma once

#include "Widget.h"
#include "ScrollBar.h"
#include "VirtualWindow.h"
#include "Color.h"
#include "Vector2d.h"

class ScrollVirtualWindow : public VirtualWindow
{
public:

    Vector2d global_offset_       = 0;
    Vector2d global_start_field_  = 0;
    Vector2d global_end_field_    = 0;
    ScrollBar *scroll_bar_        = nullptr; 

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

    void set_scroll_bar(ScrollBar *new_scroll_bar)
    {
        if (scroll_bar_ != nullptr)
        {
            std::remove(children_.begin(), children_.end(), scroll_bar_);
        }

        scroll_bar_ = new_scroll_bar;
    
        add(scroll_bar_);
    }

    void ScrollEvent (Vector2d point, Vector2d offset) override
    {
        if (offset.y_ > 0)
        {
            offset.x_ = offset.x_ <= -global_offset_.x_ ? offset.x_ :  -global_offset_.x_;
            offset.y_ = offset.y_ <= -global_offset_.y_ ? offset.y_ :  -global_offset_.y_;
        }
        
        if (offset.y_ < 0)
        {
            Vector2d max_offset =  global_offset_ + global_end_field_ - shape_;
            offset.x_ = -offset.x_ <= max_offset.x_ ? offset.x_ : - max_offset.x_;
            offset.y_ = -offset.y_ <= max_offset.y_ ? offset.y_ : - max_offset.y_;
        }

        global_offset_ += offset;

        if (scroll_bar_ != nullptr)
        {
            double coeff = (scroll_bar_->shape_.y_ - scroll_bar_->up_button_.shape_.y_ * 2 - scroll_bar_->scroll_button_.shape_.y_) /
                           (global_end_field_.y_ - global_start_field_.y_ - shape_.y_);

            scroll_bar_->scroll_button_.set_offset(offset * -1 * coeff);
        }

        for (int i = 0; i < children_.size(); i++)
        {
            if (children_[i] != scroll_bar_)
            {
                children_[i]->set_offset(offset);
            }
        }
    }

    void add(VirtualWindow *window) override
    {    
        global_start_field_.x_ = window->center_.x_ - window->shape_.x_ / 2 < global_start_field_.x_ ? 
                                 window->center_.x_ - window->shape_.x_ / 2 : global_start_field_.x_;
        global_start_field_.y_ = window->center_.y_ - window->shape_.y_ / 2 < global_start_field_.y_ ? 
                                 window->center_.y_ - window->shape_.y_ / 2 : global_start_field_.y_;

        global_end_field_.x_ = window->center_.x_ + window->shape_.x_ / 2 > global_end_field_.x_ ? 
                               window->center_.x_ + window->shape_.x_ / 2 : global_end_field_.x_;
        
        global_end_field_.y_ = window->center_.y_ + window->shape_.y_ / 2 > global_end_field_.y_ ? 
                               window->center_.y_ + window->shape_.y_ / 2 : global_end_field_.y_;

        VirtualWindow::add(window);
    }
};