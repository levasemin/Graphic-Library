#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "Object.h"
#include "Widget.h"

class CompositeObject : public Object
{

protected:
    Vector2d global_shape_;
    std::vector<Widget *> children_;

public:
    CompositeObject(Vector2d shape, Vector2d center, const Texture &texture = Texture(Color::Red)): Object(shape, center, texture),
        global_shape_(0, 0),
        children_({})
        {
        }

    void ClickLeftEvent      (const Event &event) override
    {   
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->ClickLeftEvent(event);
        }
    }

    void ReleasedLeftEvent   (const Event &event) override
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->ReleasedLeftEvent(event);
        }
    }             
    
    void ClickRightEvent     (const Event &event) override
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->ClickRightEvent(event);
        }
    }
    void ReleasedRightEvent  (const Event &event) override
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->ReleasedLeftEvent(event);
        }
    }            
    
    void MoveMouseEvent      (const Event &event) override
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->MoveMouseEvent(event);
        }
    }
    
    void PressKeyEvent       (const Event &event) override
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->PressKeyEvent(event);
        }
    }
    
    void ScrollEvent         (const Event &event) override
    {
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->ScrollEvent(event);
        }
    }  

    void set_global_offset(Vector2d offset) override
    {
        Object::set_global_offset(offset);

        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->set_global_offset(offset + get_start_field());
        }
    }

    void draw() override
    {
        render_texture_->clear();
        
        sprite_.setTexture(texture_);
        sprite_.setPosition(Vector2d(0, 0));
        render_texture_->draw(sprite_);
        
        for (size_t i = 0; i < children_.size(); i++)
        {
            children_[i]->draw();
        }

        Object::draw(); 

    }
    
    void reset_global_shape()
    {
        Vector2d global_end_field(INT64_MIN, INT64_MIN);
        Vector2d global_start_field(INT64_MAX, INT64_MAX);

        for (size_t i = 0; i < children_.size(); i++)
        {
            global_start_field.x_ = children_[i]->get_center().x_ -  children_[i]->get_shape().x_ / 2 < global_start_field.x_ ? 
                                      children_[i]->get_center().x_ -  children_[i]->get_shape().x_ / 2 : global_start_field.x_;
        
            global_start_field.y_ = children_[i]->get_center().y_ - children_[i]->get_shape().y_ / 2 < global_start_field.y_ ? 
                                      children_[i]->get_center().y_ - children_[i]->get_shape().y_ / 2 : global_start_field.y_;

            global_end_field.x_   = children_[i]->get_center().x_ +  children_[i]->get_shape().x_ / 2 > global_end_field.x_ ? 
                                    children_[i]->get_center().x_ +  children_[i]->get_shape().x_ / 2 : global_end_field.x_;
        
            global_end_field.y_   = children_[i]->get_center().y_ + children_[i]->get_shape().y_ / 2 > global_end_field.y_ ? 
                                    children_[i]->get_center().y_ + children_[i]->get_shape().y_ / 2 : global_end_field.y_;

            global_shape_ = global_end_field - global_start_field;
        }
    }

    void remove(Widget *widget) override
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

    void add(Widget *widget) override
    {
        if (widget->get_parent() == this)
        {
            return;
        }

        widget->set_parent(this);
        widget->set_global_offset(get_start_field());

        children_.push_back(widget);
        
        reset_global_shape();
    }
    
    std::vector<Widget *> get_children() const override { return children_;}
    Vector2d get_global_shape() const override         { return global_shape_; }

    void set_children(std::vector<Widget *> children) override { children_ = children; }
    void set_global_shape(Vector2d global_shape) override { global_shape_ = global_shape; }

    Vector2d get_local_offset() const override
    {
        return local_offset_; 
    }

    void set_local_offset(Vector2d offset) override
    { 
        std::vector <Widget *> children = get_children();

        for (size_t i = 0; i < children.size(); i++)
        {
            children[i]->set_global_offset(children[i]->get_global_offset() + (offset - local_offset_) * children[i]->get_has_local_offset());
        }

        local_offset_ = offset; 
    }
};