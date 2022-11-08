#pragma once

#include "Label.h"
#include "Object.h"
#include "Widget.h"
#include "Command.h"
#include "math.h"
#include "Vector2d.h"

class Button : public Object
{
public:

    bool is_left_clicked_  = false;
    bool is_right_clicked_ = false;
        
    Button(Vector2d shape, Vector2d center, const Texture &texture, Widget *parent = nullptr) : 
        Object(shape, center, texture, parent)
        {
        };
    
    void set_left_click       (Command<Vector2d> *command)
    {
        left_click_command_ = command;
    }

    void set_left_press  (Command<Vector2d> *command)
    {
        left_press_command_ = command;
    }

    void set_release_left_click  (Command<Vector2d> *command)
    {
        release_left_click_command_ = command;
    }

    void set_right_click      (Command<Vector2d> *command)
    {
        right_click_command_ = command;
    }

    void set_right_press  (Command<Vector2d> *command)
    {
        right_press_command_ = command;
    }

    void set_release_right_click  (Command<Vector2d> *command)
    {
        release_right_click_command_ = command;
    }
    

    void ClickLeftEvent     (Vector2d point)   override;
    void PressLeftEvent     (Vector2d point)   override;
    void ReleasedLeftEvent  (Vector2d point)   override;

    void ClickRightEvent    (Vector2d point)   override;
    void PressRightEvent    (Vector2d point)   override;
    void ReleasedRightEvent (Vector2d point)   override;
    
    void MoveMouseEvent     (Vector2d point)   override {};
    void PressKeyEvent      (int key)          override {};
    void ScrollEvent        (Vector2d point, Vector2d offset) override {};

    void print(Vector2d point)
    {
        printf("CLICKED!!\n");
    }

private:
    Command<Vector2d> *left_click_command_          = nullptr;
    Command<Vector2d> *left_press_command_          = nullptr;
    Command<Vector2d> *release_left_click_command_  = nullptr;

    Command<Vector2d> *right_click_command_         = nullptr;
    Command<Vector2d> *right_press_command_         = nullptr;
    Command<Vector2d> *release_right_click_command_ = nullptr;
};


void Button::ClickLeftEvent (Vector2d point)
{
    if (point_belonging(point))
    {
        is_left_clicked_ = true;
        
        if (left_click_command_ != nullptr)
        {
            left_click_command_->Execute(point);
        }
    }
}

void Button::PressLeftEvent (Vector2d point)
{
    is_left_clicked_ = true;

    if (point_belonging(point))
    {        
        if (left_press_command_ != nullptr)
        {
            left_press_command_->Execute(point);
        }
    }
}

void Button::PressRightEvent (Vector2d point)
{
    is_right_clicked_ = true;

    if (point_belonging(point))
    {        
        if (right_press_command_ != nullptr)
        {
            right_press_command_->Execute(point);
        }
    }
}

void Button::ReleasedLeftEvent (Vector2d point)
{
    is_left_clicked_ = false;

    if (point_belonging(point))
    {
        if (release_left_click_command_ != nullptr)
        {
            release_left_click_command_->Execute(point);
        }
    }
}

void Button::ClickRightEvent     (Vector2d point)
{
    if (point_belonging(point))
    {
        is_right_clicked_ = true;

        if (right_click_command_ != nullptr)
        {
            right_click_command_->Execute(point);
        }
    }
}

void Button::ReleasedRightEvent (Vector2d point)
{
    is_right_clicked_ = false;

    if (point_belonging(point))
    {
        if (release_right_click_command_ != nullptr)
        {
            release_right_click_command_->Execute(point);
        }
    }
}