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

    Command<const Event&> *scroll_command_ = nullptr;

    double scroll_button_coeff_size_;
    
    Vector2d click_place_;
    
    ScrollBar(Vector2d shape, Vector2d center, Texture texture):
        CompositeObject  (shape, center, texture),
        scroll_button_coeff_size_(scroll_button_coeff_size),
        up_button_    (Vector2d(shape.x_, shape.x_), Vector2d(shape.x_ / 2, shape.x_ / 2),
                      Texture(Colors::White)),
        down_button_  (Vector2d(shape.x_, shape.x_), Vector2d(shape.x_ / 2, shape_.y_   - shape.x_ / 2),
                       Texture(Colors::White)),
        scroll_button_(Vector2d(shape.x_, (shape.y_ - shape.x_ * 2) / scroll_button_coeff_size),
                       Vector2d(shape.x_ / 2, shape.x_ + shape_.y_ / scroll_button_coeff_size  / 2), 
                       Texture(Colors::Red))
        {
            add(&up_button_);
            add(&down_button_);
            add(&scroll_button_);
            
            down_button_.set_has_local_offset(false);
            up_button_.set_has_local_offset(false);
            
            up_button_.set_left_press    ((Command<const Event &> *) new SimpleCommand<ScrollBar, const Event &>(this, &ScrollBar::scroll_up));
            down_button_.set_left_press  ((Command<const Event &> *) new SimpleCommand<ScrollBar, const Event &>(this, &ScrollBar::scroll_down));
            scroll_button_.set_left_click((Command<const Event &> *) new SimpleCommand<ScrollBar, const Event &>(this, &ScrollBar::clicked_scroll_button));
        };

        void ScrollEvent(const Event &event) override
        {            
            Vector2d res_offset(0, event.Oleg_.smedata.value * -1);
            res_offset.x_ = local_offset_.x_ + res_offset.x_ > 0 ? res_offset.x_ : 0;
            res_offset.y_ = local_offset_.y_ + res_offset.y_ > 0 ? res_offset.y_ : 0;
            res_offset.x_ = local_offset_.x_ + res_offset.x_ < shape_.x_ - scroll_button_.get_shape().x_? res_offset.x_ : 0;
            res_offset.y_ = local_offset_.y_ + res_offset.y_ < shape_.y_ - scroll_button_.get_shape().y_ - up_button_.get_shape().y_ * 2 ? res_offset.y_ : 0;

            set_local_offset(res_offset);

            if (scroll_command_ != nullptr)
            {
                scroll_command_->Execute(event);
            }
        }

        void MoveMouseEvent (const Event &event) override
        {
            if (scroll_button_.is_left_clicked_)
            {   
                Event new_event;

                new_event.type_ = EventType::ScrollbarMoved;
                new_event.Oleg_.smedata.value = click_place_.y_ - event.Oleg_.motion.y;
                new_event.Oleg_.smedata.x = event.Oleg_.motion.x;
                new_event.Oleg_.smedata.y = event.Oleg_.motion.y;

                ScrollEvent(new_event);
                click_place_ = Vector2d(event.Oleg_.motion.x, event.Oleg_.motion.y);
            }
        };

        void scroll_up(const Event &event)
        {
            Event new_event;
            new_event.type_ = EventType::ScrollbarMoved;
            new_event.Oleg_.smedata.value = 1;
            new_event.Oleg_.smedata.x = event.Oleg_.mbedata.x;
            new_event.Oleg_.smedata.y = event.Oleg_.mbedata.y;
            ScrollEvent(new_event);
        }    

        void scroll_down(const Event &event)
        {
            Event new_event;
            new_event.type_ = EventType::ScrollbarMoved;
            new_event.Oleg_.smedata.value = -1;
            new_event.Oleg_.smedata.x = event.Oleg_.mbedata.x;
            new_event.Oleg_.smedata.y = event.Oleg_.mbedata.y;
            ScrollEvent(new_event);
        }
        

        void clicked_scroll_button(const Event &event)
        {
            click_place_ = Vector2d(event.Oleg_.mbedata.x, event.Oleg_.mbedata.y);
        }

        void set_scroll_command(Command<const Event &> *new_command)
        {
            scroll_command_ = new_command;
        }

        void draw() override
        {
            CompositeObject::draw();
        }
};