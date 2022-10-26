#pragma once

#include "Color.h"
#include "Widget.h"
#include "MainWindow.h"
#include "math.h"
#include "Vector2d.h"

class Button : public MainWindow
{
public:
    char text_[120];
    Color color_;
    
    Button(Vector2d shape, Vector2d center, const Color &color = Colors::White, const char *text = "", MainWindow *parent = nullptr) : 
        MainWindow(shape, center, color, sf::Style::Default, parent),
        color_(color)
        {
            for(int i = 0; text[i] != '\0' && i < 120; i++)
            {
                text_[i] = text[i];
            }
        };
    
    void set_left_click       (void (*new_left_click_func_)(Button *self, Vector2d point))
    {
        left_click_func_ = new_left_click_func_;
    }

    void set_miss_left_click  (void (*new_miss_left_click_func_)(Button *self, Vector2d point))
    {
        miss_left_click_func_ = miss_left_click_func_;
    }

    void set_right_click      (void (*new_right_click_func_)(Button *self, Vector2d point))
    {
        right_click_func_ = new_right_click_func_;
    }

    void set_miss_right_click (void (*new_miss_right_click_func_)(Button *self, Vector2d point))
    {
        miss_right_click_func_ = new_miss_right_click_func_;
    }

    void ClickLeftEvent     (Vector2d point)   override;
    void MissClickLeftEvent (Vector2d point)   override;
    void ClickRightEvent    (Vector2d point)   override;
    void MissClickRightEvent(Vector2d point)   override;
    void PressKeyEvent      (int key)       override;
    void ScrollEvent        (double offset) override;
    void Close              ()              override;

    bool point_belonging(Vector2d point) const override;
    void draw(int app_width) override;

private:
    void (*left_click_func_)      (Button *self, Vector2d point) = nullptr;
    void (*miss_left_click_func_) (Button *self, Vector2d point) = nullptr;
    void (*right_click_func_)     (Button *self, Vector2d point) = nullptr;
    void (*miss_right_click_func_)(Button *self, Vector2d point) = nullptr;
};


void Button::ClickLeftEvent (Vector2d point)
{
    if (left_click_func_ != nullptr)
    {
        (*left_click_func_)(this, point);
    }
}

void Button::MissClickLeftEvent  (Vector2d point)
{
    if (miss_left_click_func_ != nullptr)
    {
        (*miss_left_click_func_)(this, point);
    }
}

void Button::ClickRightEvent     (Vector2d point)
{
    if (right_click_func_ != nullptr)
    {
        (*right_click_func_)(this, point);
    }
}

void Button::MissClickRightEvent (Vector2d point)
{
    if (miss_right_click_func_ != nullptr)
    {
        (*miss_right_click_func_)(this, point);
    }
}

void Button::PressKeyEvent (int key)
{

}

void Button::ScrollEvent         (double offset)
{

}

void Button::Close()
{

}

void Button::draw(int app_width)
{        
    Vector2d start = center_ - shape_ / 2;
    Vector2d end   = center_ + shape_ / 2;

    for (int i = start.y_; i < end.y_; i++)
    {
        for (int j = start.x_; j < end.x_; j++)
        {
            field_[i * app_width + j] = color_;
        }
    }
}

bool Button::point_belonging(Vector2d point) const 
{
    return abs(point.x_ - center_.x_) < shape_.x_ / 2 && abs(point.y_ - center_.y_) < shape_.y_ / 2;
}