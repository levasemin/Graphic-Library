#pragma once

#include "Object.h"
#include "Widget.h"

class CompositeObject : public Object
{

protected:
    std::vector<Widget *> children_;

    Vector2d global_start_field_ = (0, 0);
    Vector2d global_end_field_   = (0, 0);
    Vector2d global_shape_       = (0, 0);

public:
    CompositeObject(Vector2d shape, Vector2d center, Texture texture, Widget *parent = nullptr, std::vector<Widget *> children = {}):
        Object(shape, center, texture, parent),
        children_(children)
        {
            children_ = children;

            for (int i = 0; i < children_.size(); i++)
            {
                add(children_[i]);
            }
        }

    void PressLeftEvent      (Vector2d point) override
    {   
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->PressLeftEvent(point);
        }
    }

    void PressRightEvent      (Vector2d point) override
    {   
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->PressRightEvent(point);
        }
    }

    void ClickLeftEvent      (Vector2d point) override
    {   
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->ClickLeftEvent(point);
        }
    }

    void ReleasedLeftEvent   (Vector2d point) override
    {
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->ReleasedLeftEvent(point);
        }
    }             

    void ClickRightEvent     (Vector2d point) override
    {
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->ClickRightEvent(point);
        }
    }
               
    void ReleasedRightEvent  (Vector2d point) override
    {
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->ReleasedLeftEvent(point);
        }
    }            
    
    void MoveMouseEvent      (Vector2d point) override
    {
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->MoveMouseEvent(point);
        }
    }

    void PressKeyEvent       (int key) override
    {
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->PressKeyEvent(key);
        }
    }

    void ScrollEvent         (Vector2d point, Vector2d offset) override
    {
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->ScrollEvent(point, offset);
        }
    }
       
    void set_offset(Vector2d offset) override
    {
        global_offset_ += offset;
        resize_field();

        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->set_offset(offset);
        }
    }

    void set_field() override
    {
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->set_field();
        }
    }

    void draw() override
    {
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->draw();
        }

        Object::draw(); 

    }

    void remove(Widget *widget) override
    {
        for (int i = 0; i < children_.size(); i++)
        {
            if (widget == children_[i])
            {
                children_.erase(children_.begin() + i);
            }
        }

        widget->set_parent(nullptr);
        
        Vector2d offset = shape_ / 2 - center_ - global_offset_;
        widget->set_offset(offset);
        widget->set_field();
    }

    void add(Widget *widget)
    {
        global_end_field_.x_   = widget->get_center().x_ +  widget->get_shape().x_ / 2 > global_end_field_.x_ ? 
                                 widget->get_center().x_ +  widget->get_shape().x_ / 2 : global_end_field_.x_;
        
        global_end_field_.y_   = widget->get_center().y_ +  widget->get_shape().y_ / 2 > global_end_field_.y_ ? 
                                 widget->get_center().y_ +  widget->get_shape().y_ / 2 : global_end_field_.y_;

        global_shape_ = global_end_field_;

        if (widget->get_parent() == this)
        {
            return;
        }

        widget->set_parent(this);
        children_.push_back(widget);
                
        Vector2d offset = global_offset_ + center_ - shape_ / 2;
        widget->set_offset(offset);
        widget->set_field();
    }
    
    std::vector<Widget *> get_children() { return children_;}
    Vector2d get_global_shape()          { return global_shape_; }

    void set_children(std::vector<Widget *> children) { children_ = children; }
    void set_global_shape(Vector2d global_shape)  { global_shape_ = global_shape; }
};