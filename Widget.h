#pragma once

#include "Event.h"
#include "Color.h"
#include "Window.h"
#include <iostream>
#include <vector>

class Widget
{
public: 

    Widget() {};
    
    Event<> Event_;
    Event<Widget *, point> ClickLeftEvent_;
    Event<Widget *, point> MissClickLeftEvent_;
    Event<Widget *, point> ClickRightEvent_;
    Event<Widget *, point> MissClickRightEvent_;
    Event<Widget *, int>   PressKeyEvent_;
    Event<Widget *, int>   ScrollEvent_;
    Event<Widget *>        Close_;
};