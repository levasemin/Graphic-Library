#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once
#include "Command.h"
#include "Event.h"
#include "Object.h"
#include "Text.h"

class Button : public Object
{
public:

    bool is_left_clicked_  = false;
    bool is_right_clicked_ = false;
    
    Text text_;

    Button(Vector2d shape, Vector2d center, const Texture &texture = Texture(Color::White)) : Object(shape, center, texture), text_()
    {
    };

    Button(const Button& source) : Object(*(const Object *)&source),
        text_(source.text_),
        left_click_command_         (source.left_click_command_),
        release_left_click_command_ (source.release_left_click_command_),
        right_click_command_        (source.right_click_command_),
        release_right_click_command_(source.release_right_click_command_)
    {}
    
    Button &operator=(const Button &source)
    {
        Object::operator=(*(const Object *)&source);
        
        text_ = source.text_;
        left_click_command_          = source.left_click_command_;
        release_left_click_command_  = source.release_left_click_command_;
        right_click_command_         = source.right_click_command_;
        release_right_click_command_ = source.release_right_click_command_;

        return *this;
    }

    void set_left_click       (Command<const Event &> *command)
    {
        left_click_command_ = command;
    }

    void set_release_left_click  (Command<const Event &> *command)
    {
        release_left_click_command_ = command;
    }

    void set_right_click      (Command<const Event &> *command)
    {
        right_click_command_ = command;
    }

    void set_release_right_click  (Command<const Event &> *command)
    {
        release_right_click_command_ = command;
    }
    
    Command<const Event &> * get_left_click       ()
    {
        return left_click_command_;
    }

    Command<const Event &> * get_release_left_click  ()
    {
        return release_left_click_command_;
    }

    Command<const Event &> * get_right_click      ()
    {
        return right_click_command_;
    }

    Command<const Event &> * set_release_right_click  ()
    {
        return release_right_click_command_;
    }

    void set_text(const Text &text)
    {
        text_ = text;
        sprite_.setTexture(texture_);
        render_texture_->draw(sprite_);

        Vector2d text_position(0, 0);
        text_position.x_ = shape_.x_ / 2 - text_.getGlobalBounds().x_ / 2;
        text_position.y_ = shape_.y_ / 2 - text_.getGlobalBounds().y_; 
        text_.setPosition(text_position);

        render_texture_->draw(text_); 
    }

    void ClickLeftEvent     (const Event &event) override;
    void ReleasedLeftEvent  (const Event &event) override;

    void ClickRightEvent    (const Event &event) override;
    void ReleasedRightEvent (const Event &event) override;
    
    void MoveMouseEvent     (const Event &event) override;

    void print(const Event &event)
    {
        printf("CLICKED!!\n");
    }

protected:
    Command<const Event &> *left_click_command_          = nullptr;
    Command<const Event &> *release_left_click_command_  = nullptr;

    Command<const Event &> *right_click_command_         = nullptr;
    Command<const Event &> *release_right_click_command_ = nullptr;
};

