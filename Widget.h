#pragma once
#include "Vector2d.h"

class Widget
{
public: 

    Widget() {};
    
    virtual void ClickLeftEvent      (Vector2d point)                = 0;
    virtual void MissClickLeftEvent  (Vector2d point)                = 0;
    virtual void ReleasedLeftEvent   (Vector2d point)                = 0;

    virtual void ClickRightEvent     (Vector2d point)                = 0;
    virtual void ReleasedRightEvent  (Vector2d point)                = 0;
    virtual void MissClickRightEvent (Vector2d point)                = 0;
    
    virtual void MoveMouse           (Vector2d point)                = 0;

    virtual void PressKeyEvent       (int key)                       = 0;
    virtual void ScrollEvent         (Vector2d point, double offset) = 0;
    virtual void Close               ()                              = 0;
};