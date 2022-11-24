#pragma once

#include "Texture.h"
#include "CompositeObject.h"
#include "Command.h"
#include "Button.h"
#include "SimpleCommand.h"
#include "Command.h"

const double SCROLL_COEFF = 0.1;

class ScrollBarButton : public Button
{
public:
    ScrollBarButton(Vector2d shape, Vector2d center, const Texture &texture) : Button(shape, center, texture)
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
    Vector2d scroll_field_shape;

    Command<const Event&> *scroll_command_ = nullptr;

    double scroll_coeff_;
    
    Vector2d click_place_;
    
    ScrollBar(Vector2d shape, Vector2d center):
        CompositeObject  (shape, center),
        scroll_coeff_(SCROLL_COEFF),
        up_button_    (Vector2d(shape.x_, shape.x_), Vector2d(shape.x_ / 2, shape.x_ / 2),
                      Texture(Colors::White)),
        down_button_  (Vector2d(shape.x_, shape.x_), Vector2d(shape.x_ / 2, shape_.y_   - shape.x_ / 2),
                       Texture(Colors::White)),
        scroll_button_(Vector2d(shape.x_, (shape.y_ - shape.x_ * 2) * SCROLL_COEFF),
                       Vector2d(shape.x_ / 2, shape.x_ + shape_.y_ * SCROLL_COEFF  / 2), 
                       Texture(Colors::Black)),
        scroll_field_shape(shape_.x_, shape_.y_ - shape_.x_ * 2 - scroll_button_.get_shape().y_)
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


        void set_scroll_button_size(const Vector2d &shape)
        {
            scroll_button_.set_shape(shape);
            scroll_button_.set_center(Vector2d(scroll_button_.get_shape().x_ / 2, up_button_.get_shape().y_ + scroll_button_.get_shape().y_  / 2));
            scroll_field_shape.y_ = shape_.y_ - down_button_.get_shape().x_ * 2 - scroll_button_.get_shape().y_;
            scroll_coeff_ = scroll_button_.get_shape().y_ / (shape_.y_ - down_button_.get_shape().y_ * 2);
        }


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
            Event new_event = event;
            new_event.Oleg_.smedata.value = new_event.Oleg_.smedata.value < 0 ? 0 : new_event.Oleg_.smedata.value;
            new_event.Oleg_.smedata.value = new_event.Oleg_.smedata.value > 1 ? 1 : new_event.Oleg_.smedata.value;
            
            Vector2d offset = Vector2d(0, new_event.Oleg_.smedata.value - local_offset_.y_ / scroll_field_shape.y_);
            offset *= scroll_field_shape.y_;
            scroll_button_.set_local_offset(offset);
                        
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
                new_event.Oleg_.smedata.value = (event.Oleg_.motion.y - click_place_.y_) / scroll_field_shape.y_ + local_offset_.y_ / scroll_field_shape.y_;
                new_event.Oleg_.smedata.id = (int64_t)&scroll_button_;
                
                
                scroll_bar(new_event);
                
                click_place_ = Vector2d(event.Oleg_.motion.x, event.Oleg_.motion.y);
            }
        };

        void scroll_up(const Event &event)
        {
            Event new_event;
            new_event.type_ = EventType::ScrollbarMoved;
            new_event.Oleg_.smedata.value = -scroll_coeff_ + local_offset_.y_ / scroll_field_shape.y_;
            new_event.Oleg_.smedata.id    = (int64_t)&up_button_;
            scroll_bar(new_event);
        }    

        void scroll_down(const Event &event)
        {
            Event new_event;
            new_event.type_ = EventType::ScrollbarMoved;
            new_event.Oleg_.smedata.value = scroll_coeff_ + local_offset_.y_ / scroll_field_shape.y_;
            new_event.Oleg_.smedata.id    = (int64_t)&down_button_;
            scroll_bar(new_event);
        }
        
        void ClickLeftEvent(const Event &event)
        {
            if (point_belonging(Vector2d(event.Oleg_.mbedata.x, event.Oleg_.mbedata.y)) &&
               !scroll_button_.point_belonging(Vector2d(event.Oleg_.mbedata.x, event.Oleg_.mbedata.y)) &&
               !up_button_.point_belonging(Vector2d(event.Oleg_.mbedata.x, event.Oleg_.mbedata.y)) &&
               !down_button_.point_belonging(Vector2d(event.Oleg_.mbedata.x, event.Oleg_.mbedata.y)))
            {
                Event new_event;

                new_event.type_ = EventType::ScrollbarMoved;
                new_event.Oleg_.smedata.value = (event.Oleg_.motion.y - get_start_field().y_ - up_button_.get_shape().y_) / scroll_field_shape.y_ - scroll_coeff_ / 2;
                new_event.Oleg_.smedata.id = (int64_t)&scroll_button_;
                
                scroll_bar(new_event);
                
                click_place_ = Vector2d(event.Oleg_.motion.x, event.Oleg_.motion.y);
            }
            
            CompositeObject::ClickLeftEvent(event);
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