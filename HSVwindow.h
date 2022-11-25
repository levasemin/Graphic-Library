#include "Edit.h"
#include "HSVpalette.h"
#include "CompositeObject.h"
#include "SimpleCommand.h"
#include <string.h>

class HSVwindow : public CompositeObject
{
public:
    HSVpalette hsv_palette_;
    Editor h_editor_;
    Editor s_editor_;
    Editor v_editor_;
    
    HSVwindow(Vector2d shape, Vector2d center) : CompositeObject(shape, center),
        hsv_palette_(shape * 2 / 3, shape / 3 + shape / 10),
        h_editor_(Vector2d(shape.x_ / 6, shape.y_ / 15), Vector2d(shape.x_ / 3 + shape.x_ / 5 + shape.x_ / 12, shape.y_ * 2 / 15)),
        s_editor_(Vector2d(shape.x_ / 6, shape.y_ / 15), Vector2d(shape.x_ / 3 + shape.x_ / 5 + shape.x_ / 12, shape.y_ * 4 / 15)),
        v_editor_(Vector2d(shape.x_ / 6, shape.y_ / 15), Vector2d(shape.x_ / 3 + shape.x_ / 5 + shape.x_ / 12, shape.y_ * 6 / 15))
        {
            add(&hsv_palette_);
            add(&h_editor_);
            add(&s_editor_);
            add(&s_editor_);

            h_editor_.set_editor_command((Command <std::string> *)new SimpleCommand<HSVwindow, std::string>(this, &HSVwindow::change_h));
            s_editor_.set_editor_command((Command <std::string> *)new SimpleCommand<HSVwindow, std::string>(this, &HSVwindow::change_s));
            v_editor_.set_editor_command((Command <std::string> *)new SimpleCommand<HSVwindow, std::string>(this, &HSVwindow::change_v));
        };


        void change_h(std::string string)
        {
            int new_r = std::stoi(string);
            hsv_palette_.set_h(new_r);
        }

        void change_s(std::string string)
        {
            int new_g = std::stoi(string);
            hsv_palette_.set_s(new_g);
        }

        void change_v(std::string string)
        {
            int new_b = std::stoi(string);
            hsv_palette_.set_v(new_b);  
        }

    ~HSVwindow();
};

HSVwindow::~HSVwindow()
{
}
