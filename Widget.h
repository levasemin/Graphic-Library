#pragma once

#include "Window.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "Vector2d.h"

class Widget
{
public:

    Widget() 
    {}

    virtual void ClickLeftEvent      (Vector2d point) = 0;
    virtual void PressLeftEvent      (Vector2d point) = 0;
    virtual void ReleasedLeftEvent   (Vector2d point) = 0;              

    virtual void ClickRightEvent     (Vector2d point) = 0;
    virtual void PressRightEvent     (Vector2d point) = 0;               
    virtual void ReleasedRightEvent  (Vector2d point) = 0;              
    
    virtual void MoveMouseEvent      (Vector2d point) = 0;

    virtual void PressKeyEvent       (int key) = 0;
    virtual void ScrollEvent         (Vector2d point, Vector2d offset) = 0;
    
    virtual void connect(Vector2d offset) = 0;
    virtual bool point_belonging(Vector2d point) const = 0;

    virtual void resize_field() = 0;

    virtual void draw() = 0; 

    virtual void remove(Widget *window)
    {
        std::logic_error exception("removing child to widget\n");
        throw exception;
    }

    virtual void add(Widget *window)
    {
        std::logic_error exception("adding child to widget\n");
        throw exception;
    }

    virtual void display(Window *window) = 0;

    virtual Vector2d get_center()                = 0;
    virtual Vector2d get_shape()                 = 0;
    virtual Widget  *get_parent()                = 0;
    virtual RenderTexture *get_render_texture()  = 0;
    virtual std::vector<Widget *> get_children() = 0;
    virtual Vector2d get_start_field()           = 0; 
    virtual Vector2d get_end_field()             = 0;
    virtual Vector2d get_local_offset()          = 0;
    virtual Vector2d get_global_shape()          = 0;

    virtual void set_center(Vector2d center)                        = 0;
    virtual void set_shape(Vector2d shape)                          = 0;
    virtual void set_parent(Widget *parent)                         = 0;
    //virtual void set_render_texture(RenderTexture *render_texture)  = 0;
    virtual void set_children(std::vector<Widget *> children)       = 0;
    virtual void set_local_offset(Vector2d diff_offset)             = 0;
    virtual void has_local_offset(bool has)                         = 0;
    virtual void set_global_shape(Vector2d global_shape)            = 0;
};