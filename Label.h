#pragma once
#include "Command.h"
#include "Event.h"
#include "Object.h"
#include "Text.h"

class Label : public Object
{
public:

    bool is_left_clicked_  = false;
    bool is_right_clicked_ = false;
    
    Text text_;

    Label(Vector2d shape, Vector2d center) : Object(shape, center), text_()
    {
    };
    
    void set_text(const Text &text)
    {
        render_texture_->clear();
        Sprite sprite(render_texture_->getSize(), texture_);
        render_texture_->draw(sprite);

        text_ = text;

        Vector2d text_position(0, 0);
        text_position.x_ = shape_.x_ / 2 - text_.getGlobalBounds().x_ / 2;
        text_position.y_ = shape_.y_ / 2 - text_.getGlobalBounds().y_; 
        text_.setPosition(text_position);

        render_texture_->draw(text_); 
    }
};