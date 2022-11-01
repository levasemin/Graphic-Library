#pragma once

#include "Widget.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "Sprite.h"
#include "Vector2d.h"
#include "functions.h"

class VirtualWindow : public Widget
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

    VirtualWindow *parent_;
    std::vector<VirtualWindow *> children_ = {};

    VirtualWindow(Vector2d shape, Vector2d center, Texture texture, VirtualWindow *parent = nullptr, std::vector<VirtualWindow *> children = {}):
        Widget{},
        shape_(shape),
        texture_(texture),
        sprite_(shape, texture, 0),
        center_(center),
        global_offset_(Vector2d(0, 0)), 
        parent_(parent),
        children_(children)
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

            for (int i = 0; i < children_.size(); i++)
            {
                add(children_[i]);
            }

            resize_field();
        };

    
    virtual void set_offset(Vector2d offset)
    {
        global_offset_ += offset;
        resize_field();

        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->set_offset(offset);
        }
    }

    virtual void set_field()
    {
        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->render_texture_ = render_texture_;
            children_[i]->parent_shape_ = parent_shape_;
            children_[i]->set_field();
        }
    }

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

        for (int i = 0; i < children_.size(); i++)
        {
            children_[i]->draw();
        }
    }
    

    virtual void remove(VirtualWindow *window)
    {
        for (int i = 0; i < children_.size(); i++)
        {
            if (window == children_[i])
            {
                children_.erase(children_.begin() + i);
            }
        }

        window->parent_ = nullptr;
        window->parent_shape_ = window->shape_;
        window->render_texture_  = new RenderTexture(window->shape_);
        
        Vector2d offset = shape_ / 2 - center_ - global_offset_;
        window->set_offset(offset);
        window->set_field();
    }

    virtual void add(VirtualWindow *window)
    {
        if (window->parent_ == this)
        {
            return;
        }

        window->parent_ = this;
        children_.push_back(window);

        delete window->render_texture_;
        
        window->render_texture_ = render_texture_;
        window->parent_shape_ = parent_shape_;
        
        Vector2d offset = global_offset_ + center_ - shape_ / 2;
        window->set_offset(offset);
        window->set_field();
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