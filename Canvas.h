#include "RenderTexture.h"
#include "CompositeObject.h"

class Canvas : public CompositeObject
{
    RenderTexture field_;

    Canvas (Vector2d shape, Vector2d center, Texture texture, Widget *parent = nullptr, std::vector<Widget *> children = {}) : 
        CompositeObject(shape, texture, parent, children), 
        field_(texture.getSize())
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
    
        field_.draw(sprite_);
    };

    virtual void draw()
    {   
        texture_ = field_.getTexture();

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
};