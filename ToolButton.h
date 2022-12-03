#pragma once
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "Button.h"
#include "Vector2d.h"
#include "tools.h"

class ToolButton : public Button
{
public:
    
    ToolButton(Vector2d shape, Vector2d center, const Texture &texture = Texture(Color::White)) : Button(shape, center, texture)
    {
    }
    
    ToolButton(const ToolButton &source) : Button(*(const Button *)&source),
        left_click_command_         (source.left_click_command_),
        release_left_click_command_ (source.release_left_click_command_),
        right_click_command_        (source.right_click_command_),
        release_right_click_command_(source.release_right_click_command_)
    {}
    
    ToolButton &operator= (const ToolButton &source)
    {
        Button::operator=(*(const Button *)&source);

        left_click_command_          = source.left_click_command_;
        release_left_click_command_  = source.release_left_click_command_;
        right_click_command_         = source.right_click_command_;
        release_right_click_command_ = source.release_right_click_command_;

        return *this;
    }

    void set_left_click       (Command<const booba::Event &> *command)
    {
        left_click_command_ = command;
    }

    void set_release_left_click  (Command<const booba::Event &> *command)
    {
        release_left_click_command_ = command;
    }

    void set_right_click      (Command<const booba::Event &> *command)
    {
        right_click_command_ = command;
    }

    void set_release_right_click  (Command<const booba::Event &> *command)
    {
        release_right_click_command_ = command;
    }
    

    void ClickLeftEvent     (const Event &event) override;
    void ReleasedLeftEvent  (const Event &event) override;

    void ClickRightEvent    (const Event &event) override;
    void ReleasedRightEvent (const Event &event) override;
    
    void MoveMouseEvent     (const Event &event) override;
    void PressKeyEvent      (const Event &event) override {};
    void ScrollEvent        (const Event &event) override {};

protected:
    Command<const booba::Event &> *left_click_command_          = nullptr;
    Command<const booba::Event &> *release_left_click_command_  = nullptr;

    Command<const booba::Event &> *right_click_command_         = nullptr;
    Command<const booba::Event &> *release_right_click_command_ = nullptr;
};