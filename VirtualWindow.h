#pragma once

#include "Widget.h"
#include "Texture.h"
#include "Vector2d.h"
#include "functions.h"

class VirtualWindow : public Widget
{
public:
    Vector2d center_;
    Vector2d shape_;
    Vector2d start_field_;
    Vector2d end_field_;

    Texture texture_;

    Color *field_;
    VirtualWindow *parent_;
    std::vector<VirtualWindow *> children_ = {};
    bool is_visible_ = false;

    VirtualWindow(Vector2d shape, Vector2d center, Texture texture, VirtualWindow *parent = nullptr, std::vector<VirtualWindow *> children = {}):
        Widget{},
        shape_(shape),
        texture_(texture),
        center_(center),
        parent_(parent),
        children_(children)
        {
            if (center.x_ == -1 && center.y_ == -1)
            {
                center_ = shape_ / 2;
            }

            if (parent == nullptr)
            {
                field_ = new Color[(int)(shape_.x_ * shape_.y_)]();
            }
            
            else
            {
                field_ = parent->field_;
            }

            for (int i = 0; i < children_.size(); i++)
            {
                add(children_[i]);
            }

            resize_field();
        };

    
    virtual void set_offset(Vector2d offset)
    {
        center_ += offset;
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
            children_[i]->field_ = field_;

            children_[i]->set_field();
        }
    }

    virtual bool point_belonging(Vector2d point) const
    {
        return start_field_.x_ < point.x_ && point.x_ < end_field_.x_ &&
               start_field_.y_ < point.y_ && point.y_ < end_field_.y_;
    }

    void resize_field()
    {
        start_field_ = center_ - shape_ / 2;
        end_field_   = center_ + shape_ / 2;
        
        Vector2d down_limit  = parent_ != nullptr ? parent_->center_ - parent_->shape_ / 2 : Vector2d(0, 0);
        Vector2d hight_limit = parent_ != nullptr ? parent_->center_ + parent_->shape_ / 2 : Vector2d(shape_.x_, shape_.y_);

        start_field_.x_ = start_field_.x_ < down_limit.x_ ? down_limit.x_ : start_field_.x_;
        start_field_.y_ = start_field_.y_ < down_limit.y_ ? down_limit.y_ : start_field_.y_;

        end_field_.x_ = end_field_.x_ > hight_limit.x_ ? hight_limit.x_ : end_field_.x_;
        end_field_.y_ = end_field_.y_ > hight_limit.y_ ? hight_limit.y_ : end_field_.y_;

        if (doublecmp(start_field_.x_, end_field_.x_) && (start_field_.y_, end_field_.y_))
        {
            is_visible_ =  true;
        }

        else
        {
            is_visible_ = false;
        }
    }

    virtual void draw(int app_width)
    {   
        for (int i = start_field_.y_; i < end_field_.y_; i++)
        {
            for (int j = start_field_.x_; j < end_field_.x_; j++)
            {
                int texture_index = (int)(i - (center_.y_ - shape_.y_ / 2)) * shape_.x_ + (int)(j - (center_.x_ - shape_.x_ / 2));

                field_[i * app_width + j] = texture_[texture_index];
            }
        }

        for (int i = 0; i < children_.size(); i++)
        {
            if (children_[i]->is_visible_)
            {
                children_[i]->draw(app_width);
            }
        }
    }

    virtual void add(VirtualWindow *window)
    {
        window->parent_ = this;
        children_.push_back(window);

        if (window->field_ != field_)
        {
            free(window->field_);
            window->field_ = field_;
            Vector2d offset = center_ - shape_ / 2;
            window->set_offset(offset);
            window->set_field();
        }
    }
};