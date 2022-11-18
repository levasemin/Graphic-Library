#pragma once

#include "Label.h"
#include "Object.h"
#include "Widget.h"
#include "Command.h"
#include "math.h"
#include "Vector2d.h"
#include "Event.h"

class Button : public Object
{
public:

    bool is_left_clicked_  = false;
    bool is_right_clicked_ = false;
        
    Button(Vector2d shape, Vector2d center, const Texture &texture, Widget *parent = nullptr) : 
        Object(shape, center, texture, parent)
        {
        };
    
    void set_left_click       (Command<const Event &> *command)
    {
        left_click_command_ = command;
    }

    void set_left_press  (Command<const Event &> *command)
    {
        left_press_command_ = command;
    }

    void set_release_left_click  (Command<const Event &> *command)
    {
        release_left_click_command_ = command;
    }

    void set_right_click      (Command<const Event &> *command)
    {
        right_click_command_ = command;
    }

    void set_right_press  (Command<const Event &> *command)
    {
        right_press_command_ = command;
    }

    void set_release_right_click  (Command<const Event &> *command)
    {
        release_right_click_command_ = command;
    }
    

    void ClickLeftEvent     (const Event &event) override;
    void PressLeftEvent     (const Event &event) override;
    void ReleasedLeftEvent  (const Event &event) override;

    void ClickRightEvent    (const Event &event) override;
    void PressRightEvent    (const Event &event) override;
    void ReleasedRightEvent (const Event &event) override;
    
    void MoveMouseEvent     (const Event &event) override;
    void PressKeyEvent      (const Event &event) override {};
    void ScrollEvent        (const Event &event) override {};

    void print(const Event &event)
    {
        printf("CLICKED!!\n");
    }

private:
    Command<const Event &> *left_click_command_          = nullptr;
    Command<const Event &> *left_press_command_          = nullptr;
    Command<const Event &> *release_left_click_command_  = nullptr;

    Command<const Event &> *right_click_command_         = nullptr;
    Command<const Event &> *right_press_command_         = nullptr;
    Command<const Event &> *release_right_click_command_ = nullptr;
};

void Button::MoveMouseEvent(const Event &event)
{
    if (is_left_clicked_)
    {        
        if (left_press_command_ != nullptr)
        {
            left_press_command_->Execute(event);
        }
    }

    else if (is_right_clicked_)
    {
        if (right_press_command_ != nullptr)
        {
            right_press_command_->Execute(event);
        }
    }
}

void Button::PressLeftEvent (const Event &event)
{
    if (point_belonging(Vector2d(event.Oleg_.mbedata.x, event.Oleg_.mbedata.y)))
    {
        if (left_press_command_ != nullptr)
        {
            left_press_command_->Execute(event);
        }
    }
}

void Button::PressRightEvent (const Event &event)
{
    if (point_belonging(Vector2d(event.Oleg_.mbedata.x, event.Oleg_.mbedata.y)))
    {
        if (right_press_command_ != nullptr)
        {
            right_press_command_->Execute(event);
        }
    }
}

void Button::ClickLeftEvent (const Event &event)
{
    if (point_belonging(Vector2d(event.Oleg_.mbedata.x, event.Oleg_.mbedata.y)))
    {
        is_left_clicked_ = true;
        
        if (left_click_command_ != nullptr)
        {
            left_click_command_->Execute(event);
        }
    }
}

void Button::ReleasedLeftEvent (const Event &event)
{
    is_left_clicked_ = false;

    if (release_left_click_command_ != nullptr)
    {
        release_left_click_command_->Execute(event);
    }
}

void Button::ClickRightEvent (const Event &event)
{
    if (point_belonging(Vector2d(event.Oleg_.mbedata.x, event.Oleg_.mbedata.y)))
    {
        is_right_clicked_ = true;

        if (right_click_command_ != nullptr)
        {
            right_click_command_->Execute(event);
        }
    }
}

void Button::ReleasedRightEvent (const Event &event)
{
    is_right_clicked_ = false;

    if (release_right_click_command_ != nullptr)
    {
        release_right_click_command_->Execute(event);
    }
}