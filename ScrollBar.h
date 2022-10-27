#pragma once

#include "VirtualWindow.h"
#include "ScrollVirtualWindow.h"
#include "Button.h"

void clicked_button_up(Button *self, Vector2d point);

void clicked_button_down(Button *self, Vector2d point);

void clicked_button_scroll(Button *self, Vector2d point);

void released_button_scroll(Button *self, Vector2d point);

class ScrollBar : public ScrollVirtualWindow
{
public:
    Button button_up_;
    Button button_down_;    
    Button button_scroll_;
    
    Vector2d click_place_;
    bool scroll_button_clicked_ = 0;
    
    ScrollBar(Vector2d shape, Vector2d center = {-1, -1}, Color color = Colors::White, VirtualWindow *parent = nullptr, std::vector<VirtualWindow *> children = {}):
        ScrollVirtualWindow  (shape, center, color, parent, children),
        button_up_    (Vector2d(shape.x_, shape.x_), Vector2d(center.x_, center.y_ - shape.y_ / 2 + shape.x_ / 2)),
        button_down_  (Vector2d(shape.x_, shape.x_), Vector2d(center.x_, center.y_ + shape.y_ / 2 - shape.x_ / 2)),
        button_scroll_(Vector2d(shape.x_, shape.x_), Vector2d(center.x_, center.y_ - shape.y_ / 2 + shape.x_ + 5))
        {
            add(&button_up_);
            button_up_.set_left_click(&clicked_button_up);
            add(&button_down_);
            button_down_.set_left_click(&clicked_button_down);
            add(&button_scroll_);
            button_scroll_.set_left_click(&clicked_button_scroll);
            button_scroll_.set_left_released(&released_button_scroll);
        };

        void scroll(double offset)
        {
            button_scroll_.center_.y_ += offset;
                
            if (parent_ != nullptr)
            {
                parent_->set_offset(Vector2d(0, offset));
            }
        }

        void MoveMouse (Vector2d point) override 
        {
            if (scroll_button_clicked_)
            {   
                scroll(point.y_ - click_place_.y_);
                click_place_ = point;
            }
        };
};

void clicked_button_up(Button *self, Vector2d point)
{
    ((ScrollBar *)(self->parent_))->scroll(-5);
}

void clicked_button_down(Button *self, Vector2d point)
{
    ((ScrollBar *)(self->parent_))->scroll(5);
}

void clicked_button_scroll(Button *self, Vector2d point)
{
    ((ScrollBar *)(self->parent_))->click_place_ = point;
    ((ScrollBar *)(self->parent_))->scroll_button_clicked_ = true;
}

void released_button_scroll(Button *self, Vector2d point)
{
    ((ScrollBar *)(self->parent_))->scroll_button_clicked_ = false;
}