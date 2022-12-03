#include "Button.h"

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
    if (point_belonging(Vector2d(event.Oleg_.mbedata.pos)))
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
    if (point_belonging(event.Oleg_.mbedata.pos))
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