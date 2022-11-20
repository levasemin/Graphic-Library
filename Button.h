#pragma once
#include "Command.h"
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

    void print(const Event &event)
    {
        printf("CLICKED!!\n");
    }

private:
    Command<const booba::Event &> *left_click_command_          = nullptr;
    Command<const booba::Event &> *release_left_click_command_  = nullptr;

    Command<const booba::Event &> *right_click_command_         = nullptr;
    Command<const booba::Event &> *release_right_click_command_ = nullptr;
};

void Button::MoveMouseEvent(const Event &event)
{
    if (is_left_clicked_)
    {        
        if (left_click_command_ != nullptr)
        {
            Event new_event;
            new_event.type_ = EventType::ButtonClicked;
            new_event.Oleg_.bcedata.id = (uint64_t)this;
            left_click_command_->Execute(new_event);
        }
    }

    else if (is_right_clicked_)
    {
        if (right_click_command_ != nullptr)
        {
            Event new_event;
            new_event.type_ = EventType::ButtonClicked;
            new_event.Oleg_.bcedata.id = (uint64_t)this;
            right_click_command_->Execute(new_event);
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
            Event new_event;
            new_event.type_ = EventType::ButtonClicked;
            new_event.Oleg_.bcedata.id = (uint64_t)this;
            left_click_command_->Execute(new_event);
        }
    }
}

void Button::ReleasedLeftEvent (const Event &event)
{
    is_left_clicked_ = false;

    if (release_left_click_command_ != nullptr)
    {
        Event new_event;
        new_event.type_ = EventType::ButtonClicked;
        new_event.Oleg_.bcedata.id = (uint64_t)this;
        release_left_click_command_->Execute(new_event);
    }
}

void Button::ClickRightEvent (const Event &event)
{
    if (point_belonging(Vector2d(event.Oleg_.mbedata.x, event.Oleg_.mbedata.y)))
    {
        is_right_clicked_ = true;

        if (right_click_command_ != nullptr)
        {
            Event new_event;
            new_event.type_ = EventType::ButtonClicked;
            new_event.Oleg_.bcedata.id = (uint64_t)this;
            right_click_command_->Execute(new_event);
        }
    }
}

void Button::ReleasedRightEvent (const Event &event)
{
    is_right_clicked_ = false;

    if (release_right_click_command_ != nullptr)
    {
        Event new_event;
        new_event.type_ = EventType::ButtonClicked;
        new_event.Oleg_.bcedata.id = (uint64_t)this;
        release_right_click_command_->Execute(new_event);
    }
}