#pragma once

#include <SFML/Graphics.hpp>
#include "Window.hpp"
#include "Widget.hpp"
#include "Event.hpp"

namespace SL
{
    class EventManager
    {

    public: 
        void distribute_event(Widget *window, const Event &event_);

    private:
        bool is_left_button_clicked_ = false;
        bool is_right_button_clicked_ = false;
    };
}