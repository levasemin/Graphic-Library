#pragma once

#include "Texture.h"
#include "CompositeObject.h"
#include "Command.h"
#include "Button.h"
#include "SimpleCommand.h"
#include "Command.h"

const double scroll_button_coeff_size = 10;

class ScrollBar : public CompositeObject
{
public:
    Button up_button_;
    Button down_button_;    
    Button scroll_button_;

    Command<Vector2d, Vector2d> *scroll_command_ = nullptr;

    double scroll_button_coeff_size_;
    
    Vector2d click_place_;
    
    ScrollBar(Vector2d shape, Vector2d center, Texture texture, Widget *parent = nullptr, std::vector<Widget *> children = {}):
        CompositeObject  (shape, center, texture, parent, children),
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
            add(&down_button_);
            add(&scroll_button_);
            
            up_button_.set_left_press((Command<Vector2d> *)     new SimpleCommand<ScrollBar, Vector2d>(this, &ScrollBar::scroll_up));
            down_button_.set_left_press((Command<Vector2d> *)   new SimpleCommand<ScrollBar, Vector2d>(this, &ScrollBar::scroll_down));
            scroll_button_.set_left_click((Command<Vector2d> *) new SimpleCommand<ScrollBar, Vector2d>(this, &ScrollBar::clicked_scroll_button));
        };

        void ScrollEvent(Vector2d point, Vector2d offset) override
        {
            scroll_button_.set_offset(offset);

            if (scroll_command_ != nullptr)
            {
                scroll_command_->Execute(point, offset);
            }
        }

        void MoveMouseEvent (Vector2d point)  
        {
            if (scroll_button_.is_left_clicked_)
            {   
                ScrollEvent(point, Vector2d(0, click_place_.y_ - point.y_));
                click_place_ = point;
            }
        };

        void scroll_up(Vector2d point)
        {
            ScrollEvent(point, Vector2d(0, 1));
        }    

        void scroll_down(Vector2d point)
        {
            ScrollEvent(point, Vector2d(0, -1));
        }
        

        void clicked_scroll_button(Vector2d point)
        {
            click_place_ = point;
        }

        void set_scroll_command(Command<Vector2d, Vector2d> *new_command)
        {
            scroll_command_ = new_command;
        }
};