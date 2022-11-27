#pragma once

#include "Editor.h"
#include "HSVpalette.h"
#include "CompositeObject.h"
#include "SimpleCommand.h"
#include <string.h>

class HSVwindow : public CompositeObject
{
public:
    HSVpalette hsv_palette_;
    Editor r_editor_;
    Editor g_editor_;
    Editor b_editor_;

    Color color_;

    Command<const Color &> *hsv_window_command_ = nullptr; 

    HSVwindow(Vector2d shape, Vector2d center) : CompositeObject(shape, center),
        hsv_palette_(Vector2d(shape.x_ * 2 / 3, shape.y_ * 9 / 10), Vector2d(shape.x_ / 3, shape.y_ * 9 / 20) + shape / 50),
        r_editor_(Vector2d(shape.x_ / 5, shape.y_ / 15), Vector2d((shape.x_ * 2 / 3 + shape.x_ / 50) + shape.x_ / 10 + shape.x_ / 10, shape.y_ * 2 / 15)),
        g_editor_(Vector2d(shape.x_ / 5, shape.y_ / 15), Vector2d((shape.x_ * 2 / 3 + shape.x_ / 50) + shape.x_ / 10 + shape.x_ / 10, shape.y_ * 4 / 15)),
        b_editor_(Vector2d(shape.x_ / 5, shape.y_ / 15), Vector2d((shape.x_ * 2 / 3 + shape.x_ / 50) + shape.x_ / 10 + shape.x_ / 10, shape.y_ * 6 / 15)),
        color_(0.f, 0.f, 0.f)
        {
            add(&hsv_palette_);
            add(&r_editor_);
            add(&g_editor_);
            add(&b_editor_);

            hsv_palette_.set_command    ((Command <const Color&> *) new SimpleCommand<HSVwindow, const Color&>(this, &HSVwindow::change_color));
            r_editor_.set_editor_command((Command <std::string> *)  new SimpleCommand<HSVwindow, std::string> (this, &HSVwindow::change_r));
            g_editor_.set_editor_command((Command <std::string> *)  new SimpleCommand<HSVwindow, std::string> (this, &HSVwindow::change_g));
            b_editor_.set_editor_command((Command <std::string> *)  new SimpleCommand<HSVwindow, std::string> (this, &HSVwindow::change_b));
        };

        HSVwindow(const HSVwindow &source) : CompositeObject(*(const CompositeObject *)&source),
            hsv_palette_(source.hsv_palette_),
            r_editor_(source.r_editor_),
            g_editor_(source.g_editor_),
            b_editor_(source.b_editor_),
            color_(source.color_),
            hsv_window_command_(source.hsv_window_command_)
        {}
        
        HSVwindow operator=(const HSVwindow &source)
        {
            CompositeObject::operator=(*(CompositeObject *)&source);
            hsv_palette_ = source.hsv_palette_;
            r_editor_    = source.r_editor_;
            g_editor_    = source.g_editor_;
            b_editor_    = source.b_editor_;
            
            color_ = source.color_;
            
            hsv_window_command_ = source.hsv_window_command_;
        }

        void change_color(const Color &color)
        {            
            color_ = color;

            std::string r = std::to_string(color_.get_r());
            std::string g = std::to_string(color_.get_g());
            std::string b = std::to_string(color_.get_b());
            r_editor_.setString(r);
            g_editor_.setString(g);
            b_editor_.setString(b);

            if (hsv_window_command_)
            {
                hsv_window_command_->Execute(color);
            }
        }
        
        void set_command(Command<const Color &> *command)
        {
            hsv_window_command_ = command;
        }
        
        void change_r(std::string string)
        {            
            int new_r = string.size() > 0 ? std::stoi(string) : 0;
            color_.set_r(new_r);
            hsv_palette_.set_color(color_);

            if (hsv_window_command_)
            {
                hsv_window_command_->Execute(color_);
            }
        }

        void change_g(std::string string)
        {
            int new_g = string.size() > 0 ? std::stoi(string) : 0;
            color_.set_g(new_g);
            hsv_palette_.set_color(color_);

            if (hsv_window_command_)
            {
                hsv_window_command_->Execute(color_);
            }
        }

        void change_b(std::string string)
        {
            int new_b = string.size() > 0 ? std::stoi(string) : 0;
            color_.set_b(new_b);
            hsv_palette_.set_color(color_);  
            
            if (hsv_window_command_)
            {
                hsv_window_command_->Execute(color_);
            }
        }

        void ClickLeftEvent      (const Event &event) override
    {  
        printf("$$$$$$\n");
        get_start_field().print_value();
        printf("$$$$$$\n");
        
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->ClickLeftEvent(event);
        }
    }
};