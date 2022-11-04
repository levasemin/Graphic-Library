#pragma once

#include "Widget.h"


class CompositeWidget : public Widget
{

public:
    CompositeWidget(Vector2d shape, Vector2d center, Texture texture, Widget *parent = nullptr, std::vector<Widget *> children = {}):
        Widget(shape, center, texture, parent)
        {
            children_ = children;

            for (int i = 0; i < children_.size(); i++)
            {
                add(children_[i]);
            }
        }

    void ClickLeftEvent      (Vector2d point) override
    {   
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->ClickLeftEvent(point);
        }
    }

    virtual void ReleasedLeftEvent   (Vector2d point)
    {
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->ReleasedLeftEvent(point);
        }
    }             

    virtual void ClickRightEvent     (Vector2d point)
    {
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->ClickRightEvent(point);
        }
    }
               
    virtual void ReleasedRightEvent  (Vector2d point)
    {
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->ReleasedLeftEvent(point);
        }
    }            
    
    virtual void MoveMouse           (Vector2d point)
    {
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->MoveMouse(point);
        }
    }

    virtual void PressKeyEvent       (int key)
    {
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->PressKeyEvent(key);
        }
    }

    virtual void ScrollEvent         (Vector2d point, Vector2d offset)
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
            children_[i]->render_texture_ = render_texture_;
            children_[i]->parent_shape_ = parent_shape_;
            children_[i]->set_field();
        }
    }

    void draw() override
    {
        Widget::draw();
        
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->draw();
        }
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

        widget->parent_ = nullptr;
        widget->parent_shape_ = widget->shape_;
        widget->render_texture_  = new RenderTexture(widget->shape_);
        
        Vector2d offset = shape_ / 2 - center_ - global_offset_;
        widget->set_offset(offset);
        widget->set_field();
    }

    void add(Widget *widget)
    {
        if (widget->parent_ == this)
        {
            return;
        }

        widget->parent_ = this;
        children_.push_back(widget);

        delete widget->render_texture_;
        
        widget->render_texture_ = render_texture_;
        widget->parent_shape_ = parent_shape_;
        
        Vector2d offset = global_offset_ + center_ - shape_ / 2;
        widget->set_offset(offset);
        widget->set_field();
    }
};