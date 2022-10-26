#pragma once

#include "Color.h"
#include "Window.h"
#include <iostream>
#include <vector>
#include "Vector2d.h"

class Widget
{
public: 

    Widget() {};
    
    virtual void ClickLeftEvent      (Vector2d point)   = 0;
    virtual void MissClickLeftEvent  (Vector2d point)   = 0;
    virtual void ClickRightEvent     (Vector2d point)   = 0;
    virtual void MissClickRightEvent (Vector2d point)   = 0;
    virtual void PressKeyEvent       (int key)       = 0;
    virtual void ScrollEvent         (double offset) = 0;
    virtual void Close               ()              = 0;
};