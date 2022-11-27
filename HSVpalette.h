#pragma once

#include "Object.h"
#include "Image.h"
#include "Editor.h"

class HSVpalette : public Object
{   
public:
    Color color_;

    VerticalScrollBar scroll_bar_;
    Image palette_;
    
    bool clicked_ = false;

    Command<const Color&> *palette_command_ = nullptr;

    HSVpalette(Vector2d shape, Vector2d center) : Object(shape, center),
        scroll_bar_(Vector2d(20, shape.y_), Vector2d(center.x_ + shape.x_ / 2 + 10, center.y_)),
        palette_(shape),
        color_(360.f, 0.f, 0.f)
    {   
        scroll_bar_.set_scroll_command((Command<const Event &> *) new SimpleCommand<HSVpalette, const Event&>(this, &HSVpalette::change_H));
        scroll_bar_.set_scroll_button_size(Vector2d(20, 4));
        scroll_bar_.set_button(false);
        Image scroll_bar_image(scroll_bar_.get_shape());
        
        for (float y = 0; y < scroll_bar_image.getSize().y_; y++)
        {
            for (float x = 0; x < scroll_bar_image.getSize().x_; x++)
            {
                scroll_bar_image.setPixel(Vector2d(x, y), Color((1.0 - y / scroll_bar_.get_shape().y_) * 360.f, 1.f, 1.f));
            }
        }

        scroll_bar_.set_texture(scroll_bar_image.getTexture());
    }
    
    void set_command(Command<const Color&> *command)
    {
        palette_command_ = command;
    }
    
    void draw() override
    {   
        scroll_bar_.draw();

        for (float y = 0; y < shape_.y_; y++)
        {
            for (float x = 0; x < shape_.x_; x++)
            {
                if ((int)(color_.get_s() * shape_.x_) == (int)x || (int)((1 - color_.get_v()) * shape_.y_) == (int)y)
                {
                    palette_.setPixel(Vector2d(x, y), Color::White);
                }

                else
                {
                    palette_.setPixel(Vector2d(x, y), Color(color_.get_h(), x / shape_.x_, 1.0 - y / shape_.y_));
                }
            }
        }

        Sprite sprite(shape_, palette_.getTexture());
        render_texture_->clear();
        render_texture_->draw(sprite);
        render_texture_->display();
        
        scroll_bar_.draw();
        Object::draw();
    }

    void set_color(const Color &color)
    {
        color_ = color;
        Event new_event;
        new_event.type_ = EventType::ScrollbarMoved;
        new_event.Oleg_.smedata.value = 1.0 - color_.get_h() / 360.0;
        scroll_bar_.scroll_bar(new_event);
    }

    void change_H(const Event &event)
    {
        color_.set_h((1.0 - event.Oleg_.smedata.value) * 360.0);

        if (palette_command_)
        {
            palette_command_->Execute(color_);
        }
    }

    void ClickLeftEvent (const Event &event) override
    {
        printf("!ClIck!\n"); 

        scroll_bar_.ClickLeftEvent(event);
        
        // printf("!!!!!\n");
        // Vector2d(event.Oleg_.mbedata.x, event.Oleg_.mbedata.y).print_value();
        // get_global_offset().print_value();
        // printf("?????\n");
        if (point_belonging(event.Oleg_.mbedata.pos))
        {
            printf("YEAH\n");
            clicked_ = true;

            color_.set_s((event.Oleg_.mbedata.pos.x_ - get_start_field().x_) / shape_.x_);
            color_.set_v(1.0 - (event.Oleg_.mbedata.pos.y_ - get_start_field().y_) / shape_.y_);

            if (palette_command_)
            {
                palette_command_->Execute(color_);
            }
        }

        else
        {
            clicked_ = false;
        }
    }

    void MoveMouseEvent(const Event &event) override
    {
        scroll_bar_.MoveMouseEvent(event);
        
        if (clicked_)
        {
            if (point_belonging(event.Oleg_.motion.pos))
            {
                color_.set_s((event.Oleg_.motion.pos.x_ - get_start_field().x_) / shape_.x_);
                color_.set_v(1.0 - (event.Oleg_.motion.pos.y_ - get_start_field().y_) / shape_.y_);
                
                if (palette_command_)
                {
                    palette_command_->Execute(color_);
                }
            }
        }
    }

    void ReleasedLeftEvent (const Event &event) override
    {
        clicked_ = false;
        
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