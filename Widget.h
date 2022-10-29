#pragma once
#include "Vector2d.h"

class Widget
{
public: 

    Widget() {};
    
    virtual void ClickLeftEvent      (Vector2d point) {};
    virtual void MissClickLeftEvent  (Vector2d point) {};
    virtual void ReleasedLeftEvent   (Vector2d point) {};              

    virtual void ClickRightEvent     (Vector2d point) {};               
    virtual void ReleasedRightEvent  (Vector2d point) {};              
    virtual void MissClickRightEvent (Vector2d point) {};          
    
    virtual void MoveMouse           (Vector2d point) {};

    virtual void PressKeyEvent       (int key) {};
    virtual void ScrollEvent         (Vector2d point, Vector2d offset) {};
    virtual void Close               () {};                             
};