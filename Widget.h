#pragma once

#include "Texture.h"
#include "RenderTexture.h"
#include "Sprite.h"
#include "Vector2d.h"
#include "functions.h"

class Widget
{
public:
    Vector2d global_offset_;
    Vector2d center_;
    Vector2d shape_;
    Vector2d start_field_;
    Vector2d end_field_;

    Vector2d parent_shape_;
    
    RenderTexture *render_texture_;
    Texture texture_;
    Sprite sprite_;

    Widget *parent_;
    std::vector<Widget *> children_ = {};

    Widget(Vector2d shape, Vector2d center, Texture texture, Widget *parent = nullptr):
        shape_(shape),
        texture_(texture),
        sprite_(shape, texture, 0),
        center_(center),
        global_offset_(Vector2d(0, 0)), 
        parent_(parent)
        {
            if (center.x_ == -1 && center.y_ == -1)
            {
                center_ = shape_ / 2;
            }

            if (parent == nullptr)
            {
                parent_shape_ = shape;
                render_texture_ = new RenderTexture(shape);
            }
            
            else
            {
                parent_shape_ = parent->parent_shape_;
                render_texture_ = parent->render_texture_;
            }

            resize_field();
        };

    virtual void ClickLeftEvent      (Vector2d point) {};
    virtual void ReleasedLeftEvent   (Vector2d point) {};              

    virtual void ClickRightEvent     (Vector2d point) {};               
    virtual void ReleasedRightEvent  (Vector2d point) {};              
    
    virtual void MoveMouse           (Vector2d point) {};

    virtual void PressKeyEvent       (int key) {};
    virtual void ScrollEvent         (Vector2d point, Vector2d offset) {};
    
    virtual void set_offset(Vector2d offset)
    {
        global_offset_ += offset;
        resize_field();
    }

    virtual void set_field(){}

    virtual bool point_belonging(Vector2d point) const
    {
        return global_offset_.x_ + start_field_.x_ < point.x_ && point.x_ < end_field_.x_ + global_offset_.x_ &&
               global_offset_.y_ + start_field_.y_ < point.y_ && point.y_ < end_field_.y_ + global_offset_.y_;
    }

    void resize_field()
    {
        start_field_ = global_offset_ + center_ - shape_ / 2;
        end_field_   = global_offset_ + center_ + shape_ / 2;
        
        Vector2d down_limit  = parent_ != nullptr ? parent_->global_offset_ + parent_->center_ - parent_->shape_ / 2 : Vector2d(0, 0);
        Vector2d hight_limit = parent_ != nullptr ? parent_->global_offset_ + parent_->center_ + parent_->shape_ / 2 : shape_;

        start_field_.x_ = start_field_.x_ < down_limit.x_ ? down_limit.x_ : start_field_.x_;
        start_field_.y_ = start_field_.y_ < down_limit.y_ ? down_limit.y_ : start_field_.y_;

        end_field_.x_ = end_field_.x_ > hight_limit.x_ ? hight_limit.x_ : end_field_.x_;
        end_field_.y_ = end_field_.y_ > hight_limit.y_ ? hight_limit.y_ : end_field_.y_;
        
        start_field_ -= global_offset_;
        end_field_   -= global_offset_;

        start_field_ = start_field_.x_ > end_field_.x_ || start_field_.y_ > end_field_.y_ ? end_field_ : start_field_;
    }

    virtual void draw()
    {   
        texture_ = get_texture();

        sprite_.setPosition(global_offset_ + start_field_);

        Vector2d start = start_field_ - center_ + shape_ / 2;
        Vector2d texture_shape = end_field_ - start_field_;

        start.x_         *= 1 / sprite_.getScale().x_;
        start.y_         *= 1 / sprite_.getScale().y_;
        texture_shape.x_ *= 1 / sprite_.getScale().x_;
        texture_shape.y_ *= 1 / sprite_.getScale().y_;
        
        sprite_.setTextureRect(start, texture_shape);
    
        render_texture_->draw(sprite_);
    }
    

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

    void set_textrue(Texture texture)
    {
        texture_ = texture;
    }

    Texture get_texture()
    {
        return texture_;
    }
};