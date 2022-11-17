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
    
    RenderTexture *render_texture_;
    Texture texture_;
    Sprite sprite_;
    Vector2d local_offset_;
    Vector2d global_offset_;
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
        global_offset_(Vector2d(0, 0))
        {
            if (center.x_ == -1 && center.y_ == -1)
            {
                center_ = shape_ / 2;
            }
            
            render_texture_ = new RenderTexture(shape);

            sprite_.setTexture(texture);

            render_texture_->draw(sprite_);
        };


    bool point_belonging(Vector2d point) const override
    {
        Vector2d start_field = get_start_field();
        Vector2d end_field   = get_end_field();

        return start_field.x_ < point.x_ && point.x_ < end_field.x_ &&
               start_field.y_ < point.y_ && point.y_ < end_field.y_;
    }

    Vector2d get_start_field() const override
    {
        Vector2d start_field = center_ - shape_ / 2 + global_offset_;
        Vector2d down_limit  = parent_ != nullptr ? parent_->get_start_field() : center_ - shape_ / 2;

        start_field.x_ = start_field.x_ < down_limit.x_ ? down_limit.x_ : start_field.x_;
        start_field.y_ = start_field.y_ < down_limit.y_ ? down_limit.y_ : start_field.y_;

        return start_field;
    }

    Vector2d get_end_field() const override
    {
        Vector2d end_field = center_ + shape_ / 2 + global_offset_;
        Vector2d hight_limit = parent_ != nullptr ? parent_->get_end_field()   : center_ + shape_ / 2;

        end_field.x_ = end_field.x_ > hight_limit.x_ ? hight_limit.x_ : end_field.x_;
        end_field.y_ = end_field.y_ > hight_limit.y_ ? hight_limit.y_ : end_field.y_;

        return end_field;
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


    void set_has_local_offset(bool has) override
    {
        has_local_offset_ = has;
    }

    bool get_has_local_offset () const override
    {
        return has_local_offset_;
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

    void set_texture(Texture texture)
    {
        texture_ = texture;
    }

    Texture get_texture()
    {
        return texture_;
    }

    void display(Window *window) override
    {
        render_texture_->display();
        window->draw(sprite_);
        window->display();
        window->clear();
    }
    
    Vector2d get_center() const override               { return center_; }
    Vector2d get_shape() const override               { return shape_; }
    Widget  *get_parent() const override                { return parent_; }
    RenderTexture *get_render_texture() const override { return render_texture_; }
    Vector2d get_global_shape() const override         { return shape_; }
    Vector2d get_global_offset() const override        { return global_offset_; }
    Vector2d get_local_offset() const override         { return local_offset_; }

    std::vector<Widget *> get_children() const override
    {
        // std::logic_error exception("try getting children from object\n");
        // throw exception;
        return {};
    }

    void set_center(Vector2d center) override { center_ = center; }
    void set_shape (Vector2d shape) override { shape_  = shape; }
    void set_parent(Widget *parent) override { parent_ = parent; }
    void set_render_texture(RenderTexture *render_texture) override {render_texture_ = render_texture;}
    void set_global_shape(Vector2d global_shape) override     { shape_ = global_shape; }
    
    void set_local_offset(Vector2d diff_offset) override      
    { 
        local_offset_ += diff_offset; 

        std::vector <Widget *> children = get_children();

        for (int i = 0; i < children.size(); i++)
        {
            children[i]->set_global_offset(diff_offset * children[i]->get_has_local_offset());
        }
    }

    void set_global_offset(Vector2d diff_offset) override      { global_offset_ += diff_offset; }
    void set_children(std::vector<Widget *> children) override
    {
        // std::logic_error exception("try setting children to object\n");
        // throw exception;
    }
};