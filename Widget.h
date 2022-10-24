#pragma once

#include "Event.h"
#include "Color.h"
#include "Window.h"
#include <iostream>
#include <vector>

class Widget
{
public:

    point center_ = {};
    int width_ = 0;
    int height_ = 0;
    Widget *parent_widget_ = nullptr;
    std::vector<Widget *> child_widgets_ = {};

    Widget(point center, int width, int height, Widget *parent_widget):
        center_(center),
        width_(width),
        height_(height),
        parent_widget_(parent_widget)
    {};
    
    Event<> Event_;
    Event<Widget *, point> ClickLeftEvent_;
    Event<Widget *, point> MissClickLeftEvent_;
    Event<Widget *, point> ClickRightEvent_;
    Event<Widget *, point> MissClickRightEvent_;
    Event<Widget *, int>   PressKeyEvent_;
    Event<Widget *, int>   ScrollEvent_;
    
    virtual bool point_belonging(point point) = 0;
    virtual void draw(Color *array, int app_width) = 0;
    virtual void add(Widget *widget) = 0;
};