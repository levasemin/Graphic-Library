#pragma once

#include "Widget.h"
#include "ScrollBar.h"
#include "Widget.h"
#include "Texture.h"
#include "Vector2d.h"


template<class InheritanceClass>
Widget *get_chosen_window(Widget *window, Vector2d point)
{
    Widget *chosen_window = nullptr;
    
    if (window->point_belonging(point) && dynamic_cast<InheritanceClass *> (window))
    {
        chosen_window = window;
    }
    
    for (int i = 0; i < window->children_.size(); i++)
    {
        Widget *chosen_child = get_chosen_window<InheritanceClass>(window->children_[i], point);

        if (chosen_child != nullptr)
        {
            chosen_window = chosen_child;
        }
    }
    
    return chosen_window;
}

class ScrollWidget : public CompositeWidget
{
public:

    Vector2d global_offset0_      = 0;
    Vector2d global_start_field_  = 0;
    Vector2d global_end_field_    = 0;
    ScrollBar *scroll_bar_        = nullptr;

    ScrollWidget(Vector2d shape, Vector2d center, Texture color, Widget *parent = nullptr, std::vector<Widget *> children = {}):
        CompositeWidget(shape, center, color, parent, children)
        {
        };

    void set_scroll_bar(ScrollBar *new_scroll_bar)
    {
        scroll_bar_ = new_scroll_bar;
        
        add(scroll_bar_);
    }

    void ScrollEvent (Vector2d point, Vector2d offset) override
    {
        if (offset.y_ > 0)
        {
            offset.x_ = offset.x_ <= -global_offset0_.x_ ? offset.x_ :  -global_offset0_.x_;
            offset.y_ = offset.y_ <= -global_offset0_.y_ ? offset.y_ :  -global_offset0_.y_;
        }
        
        if (offset.y_ < 0)
        {
            Vector2d max_offset =  global_offset0_ + global_end_field_ - shape_;
            offset.x_ = -offset.x_ <= max_offset.x_ ? offset.x_ : - max_offset.x_;
            offset.y_ = -offset.y_ <= max_offset.y_ ? offset.y_ : - max_offset.y_;
        }

        global_offset0_ += offset;

        if (scroll_bar_ != nullptr)
        {
            double coeff = (scroll_bar_->shape_.y_ - scroll_bar_->up_button_.shape_.y_ * 2 - scroll_bar_->scroll_button_.shape_.y_) /
                           (global_end_field_.y_ - global_start_field_.y_ - shape_.y_);

            scroll_bar_->scroll_button_.set_offset(offset * -1 * coeff);
            scroll_bar_->set_offset(offset * -1);
        }

        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->set_offset(offset);
        }
    }

    void add(Widget *window) override
    {    
        global_start_field_.x_ = window->center_.x_ - window->shape_.x_ / 2 < global_start_field_.x_ ? 
                                 window->center_.x_ - window->shape_.x_ / 2 : global_start_field_.x_;
        global_start_field_.y_ = window->center_.y_ - window->shape_.y_ / 2 < global_start_field_.y_ ? 
                                 window->center_.y_ - window->shape_.y_ / 2 : global_start_field_.y_;

        global_end_field_.x_   = window->center_.x_ + window->shape_.x_ / 2 > global_end_field_.x_ ? 
                                 window->center_.x_ + window->shape_.x_ / 2 : global_end_field_.x_;
        
        global_end_field_.y_   = window->center_.y_ + window->shape_.y_ / 2 > global_end_field_.y_ ? 
                                 window->center_.y_ + window->shape_.y_ / 2 : global_end_field_.y_;

        CompositeWidget::add(window);
    }
};