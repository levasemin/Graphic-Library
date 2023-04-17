#pragma once

#include "../Application/Window.h"
#include "../Classes/Texture.h"
#include "../Classes/RenderTexture.h"
#include "../Classes/Vector2d.h"
#include "../Event/Event.h"

class Widget
{
public:

    Widget() 
    {}

    virtual void ClickLeftEvent      (const Event &event)          = 0;
    virtual void ReleasedLeftEvent   (const Event &event)          = 0;              

    virtual void ClickRightEvent     (const Event &event)          = 0;
    virtual void ReleasedRightEvent  (const Event &event)          = 0;              
    
    virtual void MoveMouseEvent      (const Event &event)          = 0;

    virtual void PressKeyEvent       (const Event &event)          = 0;

    virtual void ScrollEvent         (const Event &event)          = 0;
    

    virtual bool point_belonging(Vector2d point) const             = 0;

    virtual void draw()                                            = 0; 

    virtual void remove(Widget *window)                            = 0;

    virtual void add(Widget *window)                               = 0;

    virtual void display(Window *window)                           = 0;


    virtual Vector2d get_position() const                            = 0;
    virtual void set_position(Vector2d position)                       = 0;

    virtual Vector2d get_shape() const                             = 0;
    virtual void set_shape(Vector2d shape)                         = 0;

    virtual Widget *get_parent() const                             = 0;
    virtual void set_parent(Widget *parent)                        = 0;

    virtual Texture get_texture() const                            = 0;
    virtual void set_texture(const Texture &texture)               = 0;

    virtual RenderTexture *get_render_texture() const              = 0;
    virtual void set_render_texture(RenderTexture *render_texture) = 0;

    virtual Vector2d get_indent() const                            = 0;
    virtual void set_indent(Vector2d)                              = 0;

    virtual Vector2d get_global_shape() const                      = 0;
    virtual void set_global_shape(Vector2d global_shape)           = 0;

    virtual Vector2d get_global_offset() const                     = 0;
    virtual void set_global_offset(Vector2d diff_offset)           = 0;

    virtual Vector2d get_local_offset() const                      = 0;
    virtual void set_local_offset(Vector2d diff_offset)            = 0;

    virtual bool get_has_local_offset()  const                     = 0;
    virtual void set_has_local_offset(bool has)                    = 0;

    virtual Vector2d get_start_field() const                       = 0; 
    virtual Vector2d get_end_field()   const                       = 0;
    
    virtual std::vector<Widget *> get_children() const             = 0;
    virtual void set_children(std::vector<Widget *> children)      = 0;

protected:
    virtual ~Widget() = default;
};