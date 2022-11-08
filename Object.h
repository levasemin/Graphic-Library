#pragma once

#include "Window.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "Sprite.h"
#include "Vector2d.h"
#include "functions.h"

class Object : public Widget
{
protected:
    Vector2d global_offset_;
    Vector2d center_;
    Vector2d shape_;
    Vector2d start_field_;
    Vector2d end_field_;
    
    RenderTexture *render_texture_;
    Texture texture_;
    Sprite sprite_;

    Widget *parent_;


public:

    Object(Vector2d shape, Vector2d center, Texture texture, Widget *parent = nullptr): Widget(),
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
                render_texture_ = new RenderTexture(shape);
            }
            
            else
            {
                render_texture_ = parent->get_render_texture();
            }

            resize_field();
        };

    virtual void ClickLeftEvent      (Vector2d point) = 0;
    virtual void PressLeftEvent      (Vector2d point) = 0;
    virtual void ReleasedLeftEvent   (Vector2d point) = 0;              

    virtual void ClickRightEvent     (Vector2d point) = 0;
    virtual void PressRightEvent     (Vector2d point) = 0;               
    virtual void ReleasedRightEvent  (Vector2d point) = 0;              
    
    virtual void MoveMouseEvent      (Vector2d point) = 0;

    virtual void PressKeyEvent       (int key) = 0;
    virtual void ScrollEvent         (Vector2d point, Vector2d offset) = 0;
    
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
        
        Vector2d down_limit  = parent_ != nullptr ? parent_->get_global_offset() + parent_->get_center() - parent_->get_shape() / 2 : Vector2d(0, 0);
        Vector2d hight_limit = parent_ != nullptr ? parent_->get_global_offset() + parent_->get_center() + parent_->get_shape() / 2 : shape_;

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

    void display(Window *window)
    {
        render_texture_->display();
        Sprite sprite(shape_, render_texture_->getTexture());    
    
        window->draw(sprite);
        window->display();
        render_texture_->clear();
    }

    Vector2d get_center() override               { return center_; }
    Vector2d get_shape() override               { return shape_; }
    Widget  *get_parent() override                { return parent_; }
    Vector2d get_global_offset() override        { return global_offset_; }
    RenderTexture *get_render_texture() override { return render_texture_; }
    Vector2d get_global_shape() override         { return shape_; }
    std::vector<Widget *> get_children() override
    {
        // std::logic_error exception("try getting children from object\n");
        // throw exception;
        return {};
    }

    void set_center(Vector2d center) override { center_ = center; }
    void set_shape (Vector2d shape) override { shape_  = shape; }
    void set_parent(Widget *parent) override { parent_ = parent; }
    void set_global_offset(Vector2d global_offset) override { global_offset_ = global_offset; }
    void set_render_texture(RenderTexture *render_texture) override {render_texture_ = render_texture;}
    void set_global_shape(Vector2d global_shape) override     { shape_ = global_shape; }
    void set_children(std::vector<Widget *> children) override
    {
        // std::logic_error exception("try setting children to object\n");
        // throw exception;
    }
};