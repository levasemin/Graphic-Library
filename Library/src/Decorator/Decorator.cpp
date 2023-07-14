#include "Decorator.hpp"

namespace SL
{
    Decorator::Decorator (Widget *widget): Widget(),
        widget_(widget)
    {
    }

    void Decorator::ClickLeftEvent      (const Event &event) 
    {
        widget_->ClickLeftEvent(event);
    }
    void Decorator::ReleasedLeftEvent   (const Event &event) 
    {
        widget_->ReleasedLeftEvent(event);
    }              

    void Decorator::ClickRightEvent (const Event &event) 
    {
        widget_->ClickRightEvent(event);
    }
            
    void Decorator::ReleasedRightEvent (const Event &event) 
    {
        widget_->ReleasedRightEvent(event);
    }              
    
    void Decorator::MoveMouseEvent (const Event &event) 
    {
        widget_->MoveMouseEvent(event);
    }

    void Decorator::PressKeyEvent (const Event &event) 
    {
        widget_->PressKeyEvent(event);
    }

    void Decorator::TextEvent (const Event &event) 
    {
        widget_->TextEvent(event);
    }
    
    void Decorator::ScrollEvent (const Event &event) 
    {
        widget_->ScrollEvent(event);
    }
    

    bool Decorator::point_belonging(Vector2d point) const 
    {
        return widget_->point_belonging(point);
    }

    void Decorator::draw() 
    {
        widget_->draw();
    }
    
    void Decorator::remove(Widget *window) 
    {
        widget_->remove(window);
    }

    void Decorator::add(Widget *window) 
    {
        widget_->add(window);
    }

    void Decorator::display(Window *window) 
    {
        widget_->display(window);
    }


    Vector2d Decorator::get_position() const 
    {
        return widget_->get_position();
    }
    void Decorator::set_position(Vector2d position) 
    {
        widget_->set_position(position);
    }

    Vector2d Decorator::get_shape() const 
    {
        return widget_->get_shape();
    }
    void Decorator::set_shape(Vector2d shape) 
    {
        widget_->set_shape(shape);
    }

    Widget *Decorator::get_parent() const 
    {
        return widget_->get_parent();
    }
    void Decorator::set_parent(Widget *parent) 
    {
        widget_->set_parent(parent);
    }

    Texture Decorator::get_texture() const 
    {
        return widget_->get_texture();
    }
    void Decorator::set_texture(const Texture &texture) 
    {
        return widget_->set_texture(texture);
    }

    RenderTexture *Decorator::get_render_texture() 
    {
        return widget_->get_render_texture();   
    }
    void Decorator::set_render_texture(RenderTexture render_texture) 
    {
        widget_->set_render_texture(render_texture);
    }

    Vector2d Decorator::get_indent() const      
    {
        return widget_->get_indent();
    }
    void Decorator::set_indent(Vector2d indent) 
    {
        widget_->set_indent(indent);
    }

    Vector2d Decorator::get_global_shape() const 
    {
        return widget_->get_global_shape();
    }
    void Decorator::set_global_offset(Vector2d offset) 
    {
        widget_->set_global_offset(offset);
    }

    Vector2d Decorator::get_global_offset() const 
    {
        return widget_->get_global_offset();
    }
    void Decorator::set_global_shape(Vector2d global_shape) 
    {
        widget_->set_global_shape(global_shape);
    }

    Vector2d Decorator::get_local_offset() const 
    {
        return widget_->get_local_offset();
    }

    void Decorator::set_local_offset(Vector2d offset) 
    {
        widget_->set_local_offset(offset);
    }

    bool Decorator::get_has_local_offset() const 
    {
        return widget_->get_has_local_offset();
    }    
    void Decorator::set_has_local_offset(bool has) 
    {
        widget_->set_has_local_offset(has);
    }

    Vector2d Decorator::get_start_field() const           
    {
        return widget_->get_start_field(); 
    }
    Vector2d Decorator::get_end_field() const           
    {
        return widget_->get_end_field(); 
    }

    std::vector<Widget *> Decorator::get_children() const 
    {
        return widget_->get_children();
    }

    void Decorator::set_children(std::vector<Widget *> children) 
    {
        widget_->set_children(children);
    }
}