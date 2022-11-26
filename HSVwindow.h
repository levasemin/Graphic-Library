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
    
    Command<const Color &> *hsv_window_command_ = nullptr; 
    Color color_;

    HSVwindow(Vector2d shape, Vector2d center) : CompositeObject(shape, center),
        hsv_palette_(shape * 2 / 3, shape / 3 + shape / 50),
        r_editor_(Vector2d(shape.x_ / 5, shape.y_ / 15), Vector2d((shape.x_ * 2 / 3 + shape.x_ / 50) + shape.x_ / 10 + shape.x_ / 10, shape.y_ * 2 / 15)),
        g_editor_(Vector2d(shape.x_ / 5, shape.y_ / 15), Vector2d((shape.x_ * 2 / 3 + shape.x_ / 50) + shape.x_ / 10 + shape.x_ / 10, shape.y_ * 4 / 15)),
        b_editor_(Vector2d(shape.x_ / 5, shape.y_ / 15), Vector2d((shape.x_ * 2 / 3 + shape.x_ / 50) + shape.x_ / 10 + shape.x_ / 10, shape.y_ * 6 / 15)),
        color_(0., 0., 0.)
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
};