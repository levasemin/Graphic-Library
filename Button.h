#pragma once

#include "Color.h"
#include "Widget.h"
#include "VirtualWindow.h"
#include "math.h"
#include "Vector2d.h"

class Button : public VirtualWindow
{
public:
    char text_[120];
    
    Button(Vector2d shape, Vector2d center, const Color &color = Colors::White, const char *text = "", VirtualWindow *parent = nullptr, std::vector<VirtualWindow *> children = {}) : 
        VirtualWindow(shape, center, color, parent, children)
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

    void set_left_released  (void (*new_left_released_func_)(Button *self, Vector2d point))
    {
        left_released_func_ = new_left_released_func_;
    }

    void set_right_click      (void (*new_right_click_func_)(Button *self, Vector2d point))
    {
        right_click_func_ = new_right_click_func_;
    }

    void set_miss_right_click (void (*new_miss_right_click_func_)(Button *self, Vector2d point))
    {
        miss_right_click_func_ = new_miss_right_click_func_;
    }

    void set_right_released  (void (*new_right_released_func_)(Button *self, Vector2d point))
    {
        right_released_func_ = new_right_released_func_;
    }

    void ClickLeftEvent     (Vector2d point)   override;
    void MissClickLeftEvent (Vector2d point)   override;
    void ReleasedLeftEvent  (Vector2d point)   override;
    void ClickRightEvent    (Vector2d point)   override;
    void MissClickRightEvent(Vector2d point)   override;
    void ReleasedRightEvent (Vector2d point)   override;
    void PressKeyEvent      (int key)       override;
    void ScrollEvent        (Vector2d point, double offset) override;
    void Close              ()              override;

private:
    void (*left_click_func_)      (Button *self, Vector2d point) = nullptr;
    void (*miss_left_click_func_) (Button *self, Vector2d point) = nullptr;
    void (*left_released_func_)   (Button *self, Vector2d point) = nullptr;
    void (*right_click_func_)     (Button *self, Vector2d point) = nullptr;
    void (*miss_right_click_func_)(Button *self, Vector2d point) = nullptr;
    void (*right_released_func_)  (Button *self, Vector2d point) = nullptr;
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

void Button::ReleasedLeftEvent (Vector2d point)
{
    if (left_released_func_ != nullptr)
    {
        (*left_released_func_)(this, point);
    }
}

void Button::ReleasedRightEvent (Vector2d point)
{
    if (right_released_func_ != nullptr)
    {
        (*right_released_func_)(this, point);
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

void Button::ScrollEvent (Vector2d point, double offset)
{

}

void Button::Close()
{

}