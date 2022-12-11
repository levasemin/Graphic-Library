#include "ToolButton.h"

void ToolButton::MoveMouseEvent(const Event &event)
{
    if (is_left_clicked_)
    {        
        if (left_click_command_ != nullptr)
        {
            Event new_event;
            new_event.type_ = EventType::ButtonClicked;
            new_event.Oleg_.bcedata.id = (uint64_t)this;
            left_click_command_->Execute(convert_event(new_event));
        }
    }

    else if (is_right_clicked_)
    {
        if (right_click_command_ != nullptr)
        {
            Event new_event;
            new_event.type_ = EventType::ButtonClicked;
            new_event.Oleg_.bcedata.id = (uint64_t)this;
            right_click_command_->Execute(convert_event(new_event));
        }
    }
}


void ToolButton::ClickLeftEvent (const Event &event)
{
    if (point_belonging(event.Oleg_.mbedata.pos))
    {
        is_left_clicked_ = true;
        
        if (left_click_command_ != nullptr)
        {
            Event new_event;
            new_event.type_ = EventType::ButtonClicked;
            new_event.Oleg_.bcedata.id = (uint64_t)this;
            left_click_command_->Execute(convert_event(new_event));
        }
    }
}

void ToolButton::ReleasedLeftEvent (const Event &event)
{
    is_left_clicked_ = false;

    if (left_release_command_ != nullptr)
    {
        Event new_event;
        new_event.type_ = EventType::ButtonClicked;
        new_event.Oleg_.bcedata.id = (uint64_t)this;
        left_release_command_->Execute(convert_event(new_event));
    }
}

void ToolButton::ClickRightEvent (const Event &event)
{
    if (point_belonging(event.Oleg_.mbedata.pos))
    {
        is_right_clicked_ = true;

        if (right_click_command_ != nullptr)
        {
            Event new_event;
            new_event.type_ = EventType::ButtonClicked;
            new_event.Oleg_.bcedata.id = (uint64_t)this;
            right_click_command_->Execute(convert_event(new_event));
        }
    }
}

void ToolButton::ReleasedRightEvent (const Event &event)
{
    is_right_clicked_ = false;

    if (right_release_command_ != nullptr)
    {
        Event new_event;
        new_event.type_ = EventType::ButtonClicked;
        new_event.Oleg_.bcedata.id = (uint64_t)this;
        right_release_command_->Execute(convert_event(new_event));
    }
}