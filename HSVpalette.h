#pragma once

#include "Object.h"
#include "Image.h"

class HSVpalette : public Object
{   
public:
    float h_ = 360.0;
    float s_;
    float v_;

    ScrollBar scroll_bar_;
    Image palette_;

    HSVpalette(Vector2d shape, Vector2d center) : Object(shape, center),
        scroll_bar_(Vector2d(20, shape.y_), Vector2d(center.x_ + shape.x_ / 2 + 10, center.y_)),
        palette_(shape)
    {
        scroll_bar_.set_scroll_command((Command<const Event &> *) new SimpleCommand<HSVpalette, const Event&>(this, &HSVpalette::change_H));
        scroll_bar_.set_scroll_button_size(Vector2d(20, 4));
        scroll_bar_.set_button(false);
        Image scroll_bar_image(scroll_bar_.get_shape());
        
        for (float y = 0; y < scroll_bar_image.getSize().y_; y++)
        {
            for (float x = 0; x < scroll_bar_image.getSize().x_; x++)
            {
                scroll_bar_image.setPixel(Vector2d(x, y), Color::convert_hsv_rgb((1.0 - y / scroll_bar_.get_shape().y_) * 360.0, 1.0, 1.0));
            }
        }

        scroll_bar_.set_texture(scroll_bar_image.getTexture());
    }
    

    void draw() override
    {   
        scroll_bar_.draw();

        for (float y = 0; y < shape_.y_; y++)
        {
            for (float x = 0; x < shape_.x_; x++)
            {
                palette_.setPixel(Vector2d(x, y), Color::convert_hsv_rgb(h_, x / shape_.x_, 1.0 - y / shape_.y_));
            }
        }

        Sprite sprite(shape_, palette_.getTexture());
        render_texture_->clear();
        render_texture_->draw(sprite);
        render_texture_->display();
        
        scroll_bar_.draw();
        Object::draw();
    }

    void change_H(const Event &event)
    {
        h_ = 360 - 360.0 * event.Oleg_.smedata.value;
    }

    void ClickLeftEvent (const Event &event) override
    {
        scroll_bar_.ClickLeftEvent(event);
        
        if (point_belonging(Vector2d(event.Oleg_.mbedata.x, event.Oleg_.mbedata.y)))
        {
            s_ = (event.Oleg_.mbedata.x - get_start_field().x_) / shape_.x_;
            v_ = 1.0 - (event.Oleg_.mbedata.y - get_start_field().y_) / shape_.y_;
        }
    }

    void ReleasedLeftEvent (const Event &event) override
    {
        scroll_bar_.ReleasedLeftEvent(event);
        Object::ReleasedLeftEvent(event);
    }              

    virtual void ClickRightEvent (const Event &event) override
    {
        scroll_bar_.ClickRightEvent(event);
        Object::ClickRightEvent(event);
    }           
    
    void ReleasedRightEvent (const Event &event) override
    {   
        scroll_bar_.ReleasedRightEvent(event);
        Object::ReleasedRightEvent(event);
    }              
    
    void MoveMouseEvent (const Event &event) override
    {
        scroll_bar_.MoveMouseEvent(event);
        Object::MoveMouseEvent(event);
    }

    void PressKeyEvent (const Event &event) override
    {
        scroll_bar_.MoveMouseEvent(event);
        Object::PressKeyEvent(event);
    }

    void set_global_offset(Vector2d offset) override
    {
        scroll_bar_.set_global_offset(offset);
        Object::set_global_offset(offset);
    }

    void display(Window *window) override
    {
        scroll_bar_.display(window);
        Object::display(window);
    }

    void set_parent(Widget *parent_widget) override
    {
        scroll_bar_.set_parent(parent_widget);
        Object::set_parent(parent_widget);
    }

    void ScrollEvent (const Event &event) override
    {
        scroll_bar_.ScrollEvent(event);
        Object::ScrollEvent(event);    
    }

};