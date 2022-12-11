#pragma once

#include "Canvas.h"
#include "Button.h"

class CanvasButton : public Button
{
public:

    CanvasButton(Vector2d shape, Vector2d center, const Texture &texture = Texture(Color::White)) : Button(shape, center, texture)
    {
        left_click_command_    = (Command<const Event &> *) new SimpleCommand<CanvasButton, const Event &>(this, &CanvasButton::CanvasClickLeftEvent);
        left_release_command_  = (Command<const Event &> *) new SimpleCommand<CanvasButton, const Event &>(this, &CanvasButton::CanvasReleasedLeftEvent);
        right_click_command_   = (Command<const Event &> *) new SimpleCommand<CanvasButton, const Event &>(this, &CanvasButton::CanvasClickRightEvent);
        right_release_command_ = (Command<const Event &> *) new SimpleCommand<CanvasButton, const Event &>(this, &CanvasButton::CanvasReleasedLeftEvent);

    }

    void set_left_click           (Command<const Event &, Canvas *> *command)
    {
        canvas_left_click_command_ = command;
    }
    void set_release_left_click   (Command<const Event &, Canvas *> *command)
    {
        canvas_left_release_command_ = command;
    }
    void set_right_click          (Command<const Event &, Canvas *> *command)
    {
        canvas_right_click_command_ = command;
    }
    void set_release_right_click  (Command<const Event &, Canvas *> *command)
    {
        canvas_right_release_command_ = command;
    }
    
    
    Command<const Event &, Canvas *> *get_left_click ()
    {
        return canvas_left_click_command_;
    }
    Command<const Event &, Canvas *> *get_release_left_click ()
    {
        return canvas_left_release_command_;
    }
    Command<const Event &, Canvas *> *get_right_click      ()
    {
        return canvas_right_click_command_;
    }
    Command<const Event &, Canvas *> *set_release_right_click  ()
    {
        return canvas_right_release_command_;
    }

    void CanvasClickLeftEvent(const Event &event)
    {
        if (canvas_left_click_command_)
        {
            canvas_left_click_command_->Execute(event, canvas_);
        }
    }
    void CanvasReleasedLeftEvent  (const Event &event)
    {
        if (canvas_left_release_command_)
        {
            canvas_left_release_command_->Execute(event, canvas_);
        }
    }
    void CanvasClickRightEvent    (const Event &event) 
    {
        if (canvas_right_click_command_)
        {
            canvas_right_click_command_->Execute(event, canvas_);
        }
    }
    void CanvasReleasedRightEvent (const Event &event) 
    {
        if (canvas_right_click_command_)
        {
            canvas_right_release_command_->Execute(event, canvas_);
        }
    }

    void set_canvas(Canvas *canvas)
    {
        canvas_ = canvas;
    }

    Canvas *get_canvas()
    {
        return canvas_;
    }

protected:
    Command<const Event &, Canvas *> *canvas_left_click_command_    = nullptr;
    Command<const Event &, Canvas *> *canvas_left_release_command_  = nullptr;
    Command<const Event &, Canvas *> *canvas_right_click_command_   = nullptr;
    Command<const Event &, Canvas *> *canvas_right_release_command_ = nullptr;  

private:
    Canvas *canvas_ = nullptr;
};