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
            children_[i]->set_render_texture(render_texture_);
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

        widget->set_parent(nullptr);
        widget->set_render_texture(new RenderTexture(widget->get_shape()));
        
        Vector2d offset = shape_ / 2 - center_ - global_offset_;
        widget->set_offset(offset);
        widget->set_field();
    }

    void add(Widget *widget)
    {
        if (widget->get_parent() == this)
        {
            return;
        }

        widget->set_parent(this);
        children_.push_back(widget);

        delete widget->get_render_texture();
        
        widget->set_render_texture(render_texture_);
        
        Vector2d offset = global_offset_ + center_ - shape_ / 2;
        widget->set_offset(offset);
        widget->set_field();
    }
};