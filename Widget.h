#pragma once

#include "Event.h"
#include "Color.h"
#include "Window.h"
#include "Application.h"

class Widget
{
public:

    point center_;
    int width_;
    int height_;
    Widget *parent_widget_ = nullptr;

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

    void show();
};

void Widget::show()
{
    app.Event_ += CreateMethodEventHandler(*this, &Widget::draw);
}