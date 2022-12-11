#pragma once

#include "Button.h"
#include "SimpleCommand.h"

class CancleButton : public Button
{
public:

    CancleButton(Vector2d shape, Vector2d center, const Texture &texture = Texture(Color::White)) : Button(shape, center, texture)
    {
        left_click_command_    = (Command<const Event &> *) new SimpleCommand<CancleButton, const Event &>(this, &CancleButton::CancleClickLeftEvent);
        left_release_command_  = (Command<const Event &> *) new SimpleCommand<CancleButton, const Event &>(this, &CancleButton::CancleReleasedLeftEvent);
        right_click_command_   = (Command<const Event &> *) new SimpleCommand<CancleButton, const Event &>(this, &CancleButton::CancleClickRightEvent);
        right_release_command_ = (Command<const Event &> *) new SimpleCommand<CancleButton, const Event &>(this, &CancleButton::CancleReleasedLeftEvent);
    }

    void set_left_click           (Command<> *command)
    {
        cancle_left_click_command_    = command;
    }
    void set_release_left_click   (Command<> *command)
    {
        cancle_left_release_command_  = command;
    }
    void set_right_click          (Command<> *command)
    {
        cancle_right_click_command_   = command;
    }
    void set_release_right_click  (Command<> *command)
    {
        cancle_right_release_command_ = command;
    }
    
    Command<> *get_left_click ()
    {
        return cancle_left_click_command_;
    }
    Command<> *get_release_left_click ()
    {
        return cancle_left_release_command_;
    }
    Command<> *get_right_click      ()
    {
        return cancle_right_click_command_;
    }
    Command<> *set_release_right_click  ()
    {
        return cancle_right_release_command_;
    }

    void CancleClickLeftEvent(const Event &event)
    {
        if (cancle_left_click_command_)
        {
            cancle_left_click_command_->Execute();
        }
    }
    void CancleReleasedLeftEvent  (const Event &event)
    {
        if (cancle_left_release_command_)
        {
            cancle_left_release_command_->Execute();
        }
    }
    void CancleClickRightEvent    (const Event &event) 
    {
        if (cancle_right_click_command_)
        {
            cancle_right_click_command_->Execute();
        }
    }
    void CancleReleasedRightEvent (const Event &event) 
    {
        if (cancle_right_release_command_)
        {
            cancle_right_release_command_->Execute();
        }
    }

protected:
    Command<> *cancle_left_click_command_    = nullptr;
    Command<> *cancle_left_release_command_  = nullptr;
    Command<> *cancle_right_click_command_   = nullptr;
    Command<> *cancle_right_release_command_ = nullptr;  

};