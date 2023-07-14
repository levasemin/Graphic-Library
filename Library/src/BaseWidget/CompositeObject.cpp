#include "CompositeObject.hpp"

namespace SL
{
    CompositeObject::CompositeObject(Vector2d shape, Vector2d position, const Texture &texture): Object(shape, position, texture),
        global_shape_(0, 0),
        children_({}),
        indent_(0, 0)
        {
        }

    CompositeObject::CompositeObject::CompositeObject(const CompositeObject &source) : Object(*(const Object *)&source),
        global_shape_(source.global_shape_),
        children_(source.children_),
        indent_(source.indent_)
        {}

    CompositeObject &CompositeObject::operator=(const CompositeObject &source)
    {
        Object::operator=(*(const Object *)&source);
        global_shape_ = source.global_shape_;
        children_ = source.children_;
        indent_ = source.indent_;
        return *this;
    }

    void CompositeObject::ClickLeftEvent      (const Event &event) 
    {   
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->ClickLeftEvent(event);
        }
    }

    void CompositeObject::ReleasedLeftEvent   (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->ReleasedLeftEvent(event);
        }
    }             
    
    void CompositeObject::ClickRightEvent     (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->ClickRightEvent(event);
        }
    }

    void CompositeObject::ReleasedRightEvent  (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->ReleasedLeftEvent(event);
        }
    }            
    
    void CompositeObject::MoveMouseEvent      (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->MoveMouseEvent(event);
        }
    }
    
    void CompositeObject::TextEvent           (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->TextEvent(event);
        }
    }

    void CompositeObject::PressKeyEvent       (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->PressKeyEvent(event);
        }
    }
    
    void CompositeObject::ScrollEvent         (const Event &event) 
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->ScrollEvent(event);
        }
    }  

    void CompositeObject::set_global_offset(Vector2d offset) 
    {
        Object::set_global_offset(offset);

        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->set_global_offset(offset + position_ + local_offset_);
        }
    }

    void CompositeObject::draw() 
    {
        render_texture_.clear();
        
        sprite_.setTexture(texture_);
        sprite_.setPosition(Vector2d(0, 0));
        render_texture_.draw(sprite_);
        
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->draw();
        }

        Object::draw();
    }
    
    void CompositeObject::reset_global_shape()
    {
        Vector2d global_end_field  (-10000000.f, -10000000.f);
        Vector2d global_start_field( 0.f,  0.f);
        
        for (size_t i = 0; i < children_.size(); i++)
        {
            global_start_field.x_ = children_[i]->get_position().x_ < global_start_field.x_ ? 
                                    children_[i]->get_position().x_ : global_start_field.x_;
        
            global_start_field.y_ = children_[i]->get_position().y_ < global_start_field.y_ ? 
                                    children_[i]->get_position().y_ : global_start_field.y_;

            global_end_field.x_   = children_[i]->get_position().x_ +  children_[i]->get_shape().x_ > global_end_field.x_ ? 
                                    children_[i]->get_position().x_ +  children_[i]->get_shape().x_ : global_end_field.x_;
        
            global_end_field.y_   = children_[i]->get_position().y_ + children_[i]->get_shape().y_ > global_end_field.y_ ? 
                                    children_[i]->get_position().y_ + children_[i]->get_shape().y_ : global_end_field.y_;

            global_shape_ = global_end_field - global_start_field;
        }

        global_shape_.x_ = global_shape_.x_ > shape_.x_ ? global_shape_.x_ : shape_.x_;
        global_shape_.y_ = global_shape_.y_ > shape_.y_ ? global_shape_.y_ : shape_.y_;
    }

    void CompositeObject::remove(Widget *widget) 
    {
        widget->set_parent(nullptr);

        for (size_t i = 0; i < children_.size(); i++)
        {
            if (widget == children_[i])
            {
                children_.erase(children_.begin() + i);
            }
        }

        widget->set_global_offset(Vector2d(0, 0));

        reset_global_shape();
    }

    void CompositeObject::add(Widget *widget) 
    {
        if (widget->get_parent() == this)
        {
            return;
        }

        widget->set_parent(this);
        widget->set_global_offset(global_offset_ + position_ + local_offset_);

        children_.push_back(widget);
        
        reset_global_shape();
    }
    
    std::vector<Widget *> CompositeObject::get_children() const         
    {
        return children_; 
    }
    
    void CompositeObject::set_children(std::vector<Widget *> children)  
    { 
        children_ = children; 
    }

    Vector2d CompositeObject::get_indent() const       
    {
        return indent_; 
    }

    void CompositeObject::set_indent(Vector2d indent)  
    { 
        indent_ = indent; 
    }

    Vector2d CompositeObject::get_global_shape() const             
    {
        return global_shape_; 
    }

    void CompositeObject::set_global_shape(Vector2d global_shape)  
    {
        global_shape_ = global_shape; 
    }

    Vector2d CompositeObject::get_local_offset() const 
    {
        return local_offset_; 
    }

    void CompositeObject::set_local_offset(Vector2d offset) 
    { 
        std::vector <Widget *> children = get_children();

        for (size_t i = 0; i < children.size(); i++)
        {
            children[i]->set_global_offset(children[i]->get_global_offset() + (offset - local_offset_) * children[i]->get_has_local_offset());
        }

        local_offset_ = offset; 
    }
}