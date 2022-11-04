#pragma once

#include "Texture.h"
#include "CompositeWidget.h"
#include "Button.h"
#include "Command/SimpleCommand.h"
#include "Command/Command.h"


class ScrollBar : public CompositeWidget
{
public:
    Button up_button_;
    Button down_button_;    
    Button scroll_button_;

    double scroll_button_coeff_size_;
    
    Vector2d click_place_;
    
    ScrollBar(Vector2d shape, Vector2d center, Texture texture, double scroll_button_coeff_size = 10, Widget *parent = nullptr, std::vector<Widget *> children = {}):
        CompositeWidget  (shape, center, texture, parent, children),
        scroll_button_coeff_size_(scroll_button_coeff_size),
        up_button_    (Vector2d(shape.x_, shape.x_), Vector2d(center.x_, start_field_.y_ + shape.x_ / 2),
                      Texture(Colors::White)),
        down_button_  (Vector2d(shape.x_, shape.x_), Vector2d(center.x_, end_field_.y_   - shape.x_ / 2),
                       Texture(Colors::White)),
        scroll_button_(Vector2d(shape.x_, (shape.y_ - shape.x_ * 2) / scroll_button_coeff_size),
                       Vector2d(center.x_, start_field_.y_ + shape.x_ + shape_.y_ / scroll_button_coeff_size  / 2), 
                       Texture(Colors::Red))
        {
            add(&up_button_);
            up_button_.set_left_click((Command<Vector2d> *)new SimpleCommand<ScrollBar, Vector2d>(this, &ScrollBar::scroll_up));
            add(&down_button_);
            down_button_.set_left_click((Command<Vector2d> *)new SimpleCommand<ScrollBar, Vector2d>(this, &ScrollBar::scroll_down));
            add(&scroll_button_);
            scroll_button_.set_left_click((Command<Vector2d> *)new SimpleCommand<ScrollBar, Vector2d>(this, &ScrollBar::clicked_scroll_button));
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

        void scroll_up(Vector2d point)
        {
            Vector2d offset = Vector2d(0, (parent_->shape_.y_ - parent_->shape_.x_ * 2) / scroll_button_coeff_size_);

            parent_->ScrollEvent(point, offset);
        }    

        void scroll_down(Vector2d point)
        {
            Vector2d offset = Vector2d(0, -((parent_->shape_.y_ - parent_->shape_.x_ * 2) / scroll_button_coeff_size_));

            parent_->ScrollEvent(point, offset);
        }

        void clicked_scroll_button(Vector2d point)
        {
            click_place_ = point;
        }
};