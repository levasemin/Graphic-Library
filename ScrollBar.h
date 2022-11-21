#pragma once

#include "Texture.h"
#include "CompositeObject.h"
#include "Command.h"
#include "Button.h"
#include "SimpleCommand.h"
#include "Command.h"

const double scroll_button_coeff_size = 10;

class ScrollBarButton : public Button
{
public:
    ScrollBarButton(Vector2d shape, Vector2d center, const Texture &texture, Widget *parent = nullptr) : Button(shape, center, texture, parent)
    {
    }

    void set_local_offset(Vector2d diff_offset) override
    {              
        diff_offset.x_ = parent_->get_local_offset().x_ + diff_offset.x_ > 0 ? diff_offset.x_ : 0 - parent_->get_local_offset().x_;
        diff_offset.y_ = parent_->get_local_offset().y_ + diff_offset.y_ > 0 ? diff_offset.y_ : 0 - parent_->get_local_offset().y_;
        diff_offset.x_ = parent_->get_local_offset().x_ + diff_offset.x_ < parent_->get_shape().x_ - shape_.x_ ? 
                                                          diff_offset.x_ : parent_->get_shape().x_ - shape_.x_ - parent_->get_local_offset().x_;
        diff_offset.y_ = parent_->get_local_offset().y_ + diff_offset.y_ < parent_->get_shape().y_ - shape_.y_ - shape_.x_ * 2 ? 
                                        diff_offset.y_ : parent_->get_shape().y_ - shape_.y_ - shape_.x_ * 2 - parent_->get_local_offset().y_;

        parent_->set_local_offset(diff_offset);
    }
};

class ScrollBar : public CompositeObject
{
public:
    Button up_button_;
    Button down_button_;    
    ScrollBarButton scroll_button_;

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
            
            up_button_.set_left_click    ((Command<const Event &> *) new SimpleCommand<ScrollBar, const Event &>(this, &ScrollBar::scroll_up));
            down_button_.set_left_click  ((Command<const Event &> *) new SimpleCommand<ScrollBar, const Event &>(this, &ScrollBar::scroll_down));
            scroll_button_.set_left_click((Command<const Event &> *) new SimpleCommand<ScrollBar, const Event &>(this, &ScrollBar::clicked_scroll_button));
        };

        void ScrollEvent(const Event &event) override
        {            
            if (point_belonging(Vector2d(event.Oleg_.sedata.x, event.Oleg_.sedata.y)))
            {
                Event new_event = event;
                new_event.Oleg_.smedata.id = (int64_t)this;
                new_event.Oleg_.smedata.value = event.Oleg_.sedata.value; 
                scroll_bar(new_event);
            }
        }

        void scroll_bar(const Event &event)
        {
            scroll_button_.set_local_offset(Vector2d(0, event.Oleg_.smedata.value * -1));

            Event new_event = event;
            new_event.type_ = EventType::ScrollbarMoved;
            new_event.Oleg_.smedata.id = (int64_t) this;
            new_event.Oleg_.smedata.value = event.Oleg_.sedata.value;

            if (scroll_command_ != nullptr)
            {
                scroll_command_->Execute(new_event);
            }
        }   

        void MoveMouseEvent (const Event &event) override
        {
            if (scroll_button_.is_left_clicked_)
            {   
                Event new_event;

                new_event.type_ = EventType::ScrollbarMoved;
                new_event.Oleg_.smedata.value = click_place_.y_ - event.Oleg_.motion.y;
                new_event.Oleg_.smedata.id = (int64_t)&scroll_button_;

                scroll_bar(new_event);
                
                click_place_ = Vector2d(event.Oleg_.motion.x, event.Oleg_.motion.y);
            }
        };

        void scroll_up(const Event &event)
        {
            Event new_event;
            new_event.type_ = EventType::ScrollbarMoved;
            new_event.Oleg_.smedata.value = (shape_.y_ - up_button_.get_shape().y_ - down_button_.get_shape().y_) / scroll_button_coeff_size_;
            new_event.Oleg_.smedata.id    = (int64_t)&up_button_;
            scroll_bar(new_event);
        }    

        void scroll_down(const Event &event)
        {
            Event new_event;
            new_event.type_ = EventType::ScrollbarMoved;
            new_event.Oleg_.smedata.value = - (shape_.y_ - up_button_.get_shape().y_ - down_button_.get_shape().y_) / scroll_button_coeff_size_;
            new_event.Oleg_.smedata.id    = (int64_t)&down_button_;
            scroll_bar(new_event);
        }
        

        void clicked_scroll_button(const Event &event)
        {
            click_place_ = Vector2d((scroll_button_.get_start_field() + scroll_button_.get_end_field()) / 2);
        }

        void set_scroll_command(Command<const Event &> *new_command)
        {
            scroll_command_ = new_command;
        }
};