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
    Vector2d global_offset_;
    Vector2d local_offset_;
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
        parent_(parent),
        local_offset_(0, 0)
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
    
    void set_offset(Vector2d offset) override
    {
        global_offset_ += offset;
        local_offset_  += offset;
        resize_field();
    }

    void set_field() override{}

    bool point_belonging(Vector2d point) const override
    {
        return global_offset_.x_ + start_field_.x_ < point.x_ && point.x_ < end_field_.x_ + global_offset_.x_ &&
               global_offset_.y_ + start_field_.y_ < point.y_ && point.y_ < end_field_.y_ + global_offset_.y_;
    }

    void resize_field()
    {
        start_field_ = global_offset_ + center_ - shape_ / 2;
        end_field_   = global_offset_ + center_ + shape_ / 2;
        
        Vector2d down_limit  = parent_ != nullptr ? parent_->get_global_offset() + parent_->get_start_field() : Vector2d(0, 0);
        Vector2d hight_limit = parent_ != nullptr ? parent_->get_global_offset() + parent_->get_end_field()   : shape_;

        start_field_.x_ = start_field_.x_ < down_limit.x_ ? down_limit.x_ : start_field_.x_;
        start_field_.y_ = start_field_.y_ < down_limit.y_ ? down_limit.y_ : start_field_.y_;

        end_field_.x_ = end_field_.x_ > hight_limit.x_ ? hight_limit.x_ : end_field_.x_;
        end_field_.y_ = end_field_.y_ > hight_limit.y_ ? hight_limit.y_ : end_field_.y_;
        
        start_field_ -= global_offset_;
        end_field_   -= global_offset_;

        start_field_ = start_field_.x_ > end_field_.x_ || start_field_.y_ > end_field_.y_ ? end_field_ : start_field_;
    }

    void redraw(Texture texture)
    {        
        // sprite_.setTexture(texture);
        
        // sprite_.setPosition(start_field_);
        // Vector2d start = start_field_ - center_ + shape_ / 2;
        // Vector2d texture_shape = end_field_ - start_field_;

        // start.x_         *= 1 / sprite_.getScale().x_;
        // start.y_         *= 1 / sprite_.getScale().y_;
        // texture_shape.x_ *= 1 / sprite_.getScale().x_;
        // texture_shape.y_ *= 1 / sprite_.getScale().y_;
        
        // sprite_.setTextureRect(start, texture_shape);
    }    

    void draw() override
    {   
        render_texture_->display();
        sprite_.setTexture(render_texture_->getTexture());

        if (parent_)
        {
            //sprite_.setPosition(local_offset_ + center_ - shape_ / 2);
            
            printf("!!!!!!!!!!!\n");
            (local_offset_ + center_ - shape_ / 2).print_value();
            (center_ - shape_ / 2).print_value();
            printf("??????????\n");
            sprite_.setPosition(center_ - shape_ / 2);
            parent_->get_render_texture()->draw(sprite_);
        }
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
        redraw(render_texture_->getTexture());
        window->draw(sprite_);
        window->display();
        window->clear();
        //render_texture_->clear();
    }

    Vector2d get_center() override               { return center_; }
    Vector2d get_shape() override               { return shape_; }
    Widget  *get_parent() override                { return parent_; }
    Vector2d get_global_offset() override        { return global_offset_; }
    RenderTexture *get_render_texture() override { return render_texture_; }
    Vector2d get_global_shape() override         { return shape_; }
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
    void set_global_offset(Vector2d global_offset) override { global_offset_ = global_offset; }
    // void set_render_texture(RenderTexture *render_texture) override {render_texture_ = render_texture;}
    void set_global_shape(Vector2d global_shape) override     { shape_ = global_shape; }
    void set_children(std::vector<Widget *> children) 
    {
        // std::logic_error exception("try setting children to object\n");
        // throw exception;
    }
};