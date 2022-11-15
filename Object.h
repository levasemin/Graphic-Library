#pragma once

#include "Window.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "Sprite.h"
#include "Vector2d.h"
#include "functions.h"

class Object : public Widget
{
public:
    Vector2d center_;
    Vector2d shape_;
    Vector2d start_field_;
    Vector2d end_field_;
    
    RenderTexture *render_texture_;
    Texture texture_;
    Sprite sprite_;
    Vector2d local_offset_;
    Widget *parent_;

    bool has_local_offset_ = true;

public:

    Object(Vector2d shape, Vector2d center, Texture texture, Widget *parent = nullptr): Widget(),
        shape_(shape),
        texture_(texture),
        sprite_(shape, texture, 0),
        center_(center),    
        parent_(parent),
        local_offset_(Vector2d(0, 0)),
        start_field_(center - shape / 2),
        end_field_(center + shape / 2)
        {
            if (center.x_ == -1 && center.y_ == -1)
            {
                center_ = shape_ / 2;
            }
            
            resize_field();

            render_texture_ = new RenderTexture(shape);

            sprite_.setTexture(texture);

            render_texture_->draw(sprite_);
        };

    void ClickLeftEvent      (Vector2d point) override = 0;
    void PressLeftEvent      (Vector2d point) override = 0;
    void ReleasedLeftEvent   (Vector2d point) override = 0;              

    void ClickRightEvent     (Vector2d point) override = 0;
    void PressRightEvent     (Vector2d point) override = 0;               
    void ReleasedRightEvent  (Vector2d point) override = 0;              
    
    void MoveMouseEvent      (Vector2d point) override = 0;

    void PressKeyEvent       (int key) override = 0;
    void ScrollEvent         (Vector2d point, Vector2d offset) override = 0;
    
    void connect(Vector2d offset) override
    {
        start_field_  += offset;
        end_field_    += offset;
        resize_field();
    }

    bool point_belonging(Vector2d point) const override
    {
        return start_field_.x_ < point.x_ && point.x_ < end_field_.x_ &&
               start_field_.y_ < point.y_ && point.y_ < end_field_.y_;
    }

    void resize_field()
    {        
        //start_field_ = center_ - shape_ / 2 + (parent_ ? parent_->get_local_offset() * has_local_offset_ : Vector2d(0, 0)); 
        //end_field_   = center_ + shape_ / 2 + (parent_ ? parent_->get_local_offset() * has_local_offset_ : Vector2d(0, 0));

        Vector2d down_limit  = parent_ != nullptr ? parent_->get_start_field() : center_ - shape_ / 2;
        Vector2d hight_limit = parent_ != nullptr ? parent_->get_end_field()   : center_ + shape_ / 2;

        start_field_.x_ = start_field_.x_ < down_limit.x_ ? down_limit.x_ : start_field_.x_;
        start_field_.y_ = start_field_.y_ < down_limit.y_ ? down_limit.y_ : start_field_.y_;

        end_field_.x_ = end_field_.x_ > hight_limit.x_ ? hight_limit.x_ : end_field_.x_;
        end_field_.y_ = end_field_.y_ > hight_limit.y_ ? hight_limit.y_ : end_field_.y_;
        
        start_field_ = start_field_.x_ > end_field_.x_ || start_field_.y_ > end_field_.y_ ? end_field_ : start_field_;
    } 

    void draw() override
    {   
        render_texture_->display();
        sprite_.setTexture(render_texture_->getTexture());

        if (parent_)
        {
            sprite_.setPosition(parent_->get_local_offset() * has_local_offset_ + center_ - shape_ / 2);
            parent_->get_render_texture()->draw(sprite_);
        }
    }
    
    Vector2d get_physical_start() const
    {
        return start_field_ + (parent_ ? parent_->get_local_offset() * has_local_offset_ : Vector2d(0, 0));
    }

    Vector2d get_physical_end() const
    {
        return end_field_ + (parent_ ? parent_->get_local_offset() * has_local_offset_ : Vector2d(0, 0));
    }

    void has_local_offset(bool has)
    {
        has_local_offset_ = has;
    }

    void remove(Widget *window) override
    {
        std::logic_error exception("removing child to widget\n");
        throw exception;
    }

    void add(Widget *window) override
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
        window->draw(sprite_);
        window->display();
        window->clear();
    }

    Vector2d get_center() override               { return center_; }
    Vector2d get_shape() override               { return shape_; }
    Widget  *get_parent() override                { return parent_; }
    RenderTexture *get_render_texture() override { return render_texture_; }
    Vector2d get_global_shape() override         { return shape_; }
    Vector2d get_local_offset() override         { return local_offset_; }
    Vector2d get_start_field() override          { return start_field_; }
    Vector2d get_end_field()   override          { return end_field_; }

    std::vector<Widget *> get_children() override
    {
        // std::logic_error exception("try getting children from object\n");
        // throw exception;
        return {};
    }

    void set_center(Vector2d center) override { center_ = center; }
    void set_shape (Vector2d shape) override { shape_  = shape; }
    void set_parent(Widget *parent) override { parent_ = parent; }
    // void set_render_texture(RenderTexture *render_texture) override {render_texture_ = render_texture;}
    void set_global_shape(Vector2d global_shape) override     { shape_ = global_shape; }
    void set_local_offset(Vector2d diff_offset) override      { local_offset_ += diff_offset; }
    void set_children(std::vector<Widget *> children) 
    {
        // std::logic_error exception("try setting children to object\n");
        // throw exception;
    }
};