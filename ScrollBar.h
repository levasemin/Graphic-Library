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
        button_up_    (Vector2d(shape.x_, shape.x_), Vector2d(center.x_, start_field_.y_ + shape.x_ / 2)),
        button_down_  (Vector2d(shape.x_, shape.x_), Vector2d(center.x_, end_field_.y_   - shape.x_ / 2)),
        button_scroll_(Vector2d(shape.x_, shape.x_), Vector2d(center.x_, start_field_.y_ + shape.x_ * 1.5), Colors::Red)
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
            if ((button_up_.end_field_.y_     >= button_scroll_.start_field_.y_ + offset && offset < 0)|| 
                (button_down_.start_field_.y_ <= button_scroll_.end_field_.y_   + offset && offset > 0))
            {
                return;
            }

            button_scroll_.set_offset(Vector2d(0, offset));
            
            if (parent_ != nullptr)
            {
                for (int i = 0; i < parent_->children_.size(); i++)
                {
                    if (parent_->children_[i] == this)
                    {
                        continue;
                    }
                    
                    parent_->children_[i]->set_offset(Vector2d(0, offset));
                }
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