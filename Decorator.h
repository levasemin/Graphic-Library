#pragma once

#include "Widget.h"

class Decorator : public Widget
{

protected:
    Widget *widget_ = nullptr;

public:
    Decorator (Widget *widget): Widget(),
        widget_(widget)
    {
    }

    void ClickLeftEvent      (Vector2d point) override
    {
        widget_->ClickLeftEvent(point);
    }
    
    void PressLeftEvent      (Vector2d point) override
    {
        widget_->PressLeftEvent(point);
    }
    
    void ReleasedLeftEvent   (Vector2d point) override
    {
        widget_->ReleasedLeftEvent(point);
    }              

    virtual void ClickRightEvent     (Vector2d point) override
    {
        widget_->ClickRightEvent(point);
    }

    void PressRightEvent     (Vector2d point) override
    {
        widget_->PressRightEvent(point);
    }               
    
    void ReleasedRightEvent  (Vector2d point) override
    {
        widget_->ReleasedRightEvent(point);
    }              
    
    void MoveMouseEvent      (Vector2d point) override
    {
        widget_->MoveMouseEvent(point);
    }

    void PressKeyEvent       (int key) override
    {
        widget_->PressKeyEvent(key);
    }

    void ScrollEvent         (Vector2d point, Vector2d offset) override
    {
        widget_->ScrollEvent(point, offset);
    }
    
    void connect(Vector2d offset) override
    {
        widget_->connect(offset);
    }

    bool point_belonging(Vector2d point) const override
    {
        return widget_->point_belonging(point);
    }

    void resize_field() override
    {
        widget_->resize_field();
    }

    void remove(Widget *window) override
    {
        widget_->remove(window);
    }

    void add(Widget *window) override
    {
        widget_->add(window);
    }
    
    void draw() override
    {
        widget_->draw();
    }

    void display(Window *window) override
    {
        widget_->display(window);
    }

    Vector2d get_center() override
    {
        return widget_->get_center();
    }

    Vector2d get_shape() override
    {
        return widget_->get_shape();
    }
    Widget  *get_parent() override
    {
        return widget_->get_parent();
    }

    RenderTexture *get_render_texture() override
    {
        return widget_->get_render_texture();
    }

    std::vector<Widget *> get_children() override
    {
        return widget_->get_children();
    }
    
    Vector2d get_global_shape() override
    {
        return widget_->get_global_shape();
    }

    void set_center(Vector2d center) override
    {
        widget_->set_center(center);
    }

    void set_shape(Vector2d shape) override
    {
        widget_->set_shape(shape);
    }

    void set_parent(Widget *parent) override
    {
        widget_->set_parent(parent);
    }

    Vector2d get_local_offset()
    {
        return widget_->get_local_offset();
    }

    void set_local_offset(Vector2d diff_offset)
    {
        widget_->set_local_offset(diff_offset);
    }

    void has_local_offset(bool has)
    {
        widget_->has_local_offset(has);
    }
    
    Vector2d get_start_field() override          
    {
        return widget_->get_start_field(); 
    }

    Vector2d get_end_field()   override          
    {
        return widget_->get_end_field(); 
    }

    void set_children(std::vector<Widget *> children) override
    {
        widget_->set_children(children);
    }

    void set_global_shape(Vector2d global_shape) override
    {
        widget_->set_global_shape(global_shape);
    }
};