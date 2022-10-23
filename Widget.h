#pragma once

#include "Event.h"
#include "Color.h"
#include "Window.h"

class Widget
{
public:

    point center_;
    int width_;
    int height_;

    Widget(point center, int width, int height):
        center_(center),
        width_(width),
        height_(height)
    {};

    Event<Widget *, point> ClickLeftEvent_;
    Event<Widget *, point> MissClickLeftEvent_;
    Event<Widget *, point> ClickRightEvent_;
    Event<Widget *, point> MissClickRightEvent_;
    Event<Widget *, int>   PressKeyEvent_;
    Event<Widget *, int>   ScrollEvent_;
    
    virtual bool point_belonging(point point) = 0;
    virtual void draw(class Window *window) = 0;
    virtual void draw(class Window *window, point center) = 0;
};