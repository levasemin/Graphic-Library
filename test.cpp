#pragma once

#include "VirtualWindow.h"
#include "Button.h"

void clicked_up_button(Button *self, Vector2d point);

void clicked_down_button(Button *self, Vector2d point);

void clicked_scroll_button(Button *self, Vector2d point);

void released_scroll_button(Button *self, Vector2d point);

class ScrollBar : public VirtualWindow
{
public:
    Button up_button_;
    Button down_button_;    
    Button scroll_button_;
    double scroll_button_coeff_size_ = 10.0;
    Vector2d click_place_;
    
    ScrollBar(Vector2d shape, Vector2d center = {-1, -1}, Color color = Colors::White, VirtualWindow *parent = nullptr, std::vector<VirtualWindow *> children = {}):
        VirtualWindow  (shape, center, color, parent, children),
        up_button_    (Vector2d(shape.x_, shape.x_), Vector2d(center.x_, start_field_.y_ + shape.x_ / 2)),
        down_button_  (Vector2d(shape.x_, shape.x_), Vector2d(center.x_, end_field_.y_   - shape.x_ / 2)),
        scroll_button_(Vector2d(shape.x_, (shape.y_ - shape.x_ * 2) / scroll_button_coeff_size_),
                       Vector2d(center.x_, start_field_.y_ + shape.x_ + shape_.y_ / scroll_button_coeff_size_), Colors::Red)
        {
            add(&up_button_);
            up_button_.set_left_click(&clicked_up_button);
            add(&down_button_);
            down_button_.set_left_click(&clicked_down_button);
            add(&scroll_button_);
            scroll_button_.set_left_click(&clicked_scroll_button);
        };

        void MoveMouse (Vector2d point) override 
        {
            if (scroll_button_.is_left_clicked_)
            {   
                if (parent_)
                {
                    parent_->ScrollEvent(point, Vector2d(0, click_place_.y_ - point.y_));
                }
                
                click_place_ = point;
            }
        };

        void ScrollEvent(Vector2d point, Vector2d offset) override
        {
            if (parent_)
            {
                parent_->ScrollEvent(point, offset);
            }
        }
};

void clicked_up_button(Button *self, Vector2d point)
{
    ScrollBar *parent = (ScrollBar *)self->parent_;

    Vector2d offset = Vector2d(0, ((parent)->shape_.y_ - (parent->shape_.x_ * 2) / parent->scroll_button_coeff_size_));
    parent->ScrollEvent(point, offset);
}

void clicked_down_button(Button *self, Vector2d point)
{
    ScrollBar *parent = (ScrollBar *)self->parent_;
    Vector2d offset = Vector2d(0, -((parent->shape_.y_ - parent->shape_.x_ * 2) / parent->scroll_button_coeff_size_));
    parent->ScrollEvent(point, offset);
}

void clicked_scroll_button(Button *self, Vector2d point)
{
    ScrollBar *parent = (ScrollBar *)self->parent_;

    parent->click_place_ = point;
}