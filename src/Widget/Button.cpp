#include "Button.hpp"

namespace SL
{
    Button::Button(Vector2d shape, Vector2d position, const Texture &texture) : Object(shape, position, texture), 
        default_sprite_color_(getColor()),
        text_()
    {
        text_.setFont(Font::Times_new_roman);
    };

    Command<>* Button::getLeftClick ()
    {
        return left_click_command_;
    }
    void Button::setLeftClick (Command<>* command)
    {
        left_click_command_ = command;
    }
    
    Command<>* Button::getReleaseLeftClick ()
    {
        return left_release_command_;
    }
    void Button::setReleaseLeftClick (Command<>* command)
    {
        left_release_command_ = command;
    }
    
    Command<>* Button::getRightClick ()
    {
        return right_click_command_;
    }
    void Button::setRightClick (Command<>* command)
    {
        right_click_command_ = command;
    }
    
    Command<>* Button::getReleaseRightClick ()
    {
        return right_release_command_;
    }
    void Button::setReleaseRightClick (Command<>* command)
    {
        right_release_command_ = command;
    }

    void Button::setText(const std::string &text)
    {
        text_.setString(text);
        setText(text_);
    }

    void Button::setTextColor(const Color &color)
    {
        text_.setColor(color);
        setText(text_);
    }

    void Button::setCharacterSize(int text_size)
    {
        text_.setCharacterSize(text_size);
        setText(text_);
    }

    void Button::setText(const Text &text)
    {
        //TODO
        // text_ = text;
        // sprite_.setTexture(texture_);
        // render_texture_.draw(sprite_);

        // Vector2d text_position(0, 0);
        // text_position.x_ = shape_.x_ / 2 - text_.getGlobalBounds().x_ / 2;
        // text_position.y_ = shape_.y_ / 2 - text_.getGlobalBounds().y_; 
        // text_.setPosition(text_position);

        // render_texture_.draw(text_); 
    }

    void Button::setTexture(const Texture &texture)
    {
        Object::setTexture(texture);
        default_sprite_color_ = getColor();
    }

    void Button::clickLeftEvent (const Event &event)
    {   
        if (pointBelong(Vector2d(event.Oleg_.mpedata.pos)))
        {
            is_left_clicked_ = true;

            if (left_click_command_ != nullptr)
            {
                left_click_command_->Execute();
            }
        }
    }

    void Button::releaseLeftEvent (const Event &event)
    {
        if (left_release_command_ != nullptr)
        {
            left_release_command_->Execute();
        }

        is_left_clicked_ = false;
    }

    void Button::clickRightEvent (const Event &event)
    {
        if (pointBelong(event.Oleg_.mpedata.pos))
        {
            is_right_clicked_ = true;

            if (right_click_command_ != nullptr)
            {
                right_click_command_->Execute();
            }
        }
    }

    void Button::releaseRightEvent (const Event &event)
    {
        if (right_release_command_ != nullptr)
        {
            right_release_command_->Execute();
        }

        is_right_clicked_ = false;
    }

    void Button::moveMouseEvent(const Event &event)
    {        
        if (pointBelong(event.Oleg_.metion.pos))
        {
            Color new_color = default_sprite_color_;
        
            new_color.set_v(new_color.get_v() / 3 * 2);

            setColor(new_color);
        }

        else
        {
            setColor(default_sprite_color_);
        }   
    }

    void Button::scrollEvent(const Event &event)
    {
        if (pointBelong(event.Oleg_.mwsedata.pos))
        {
            Color new_color = default_sprite_color_;
        
            new_color.set_v(new_color.get_v() / 3 * 2);

            setColor(new_color);
        }

        else
        {
            setColor(default_sprite_color_);
        }
    }

    bool Button::isLeftClicked()
    {
        return is_left_clicked_;
    }

    bool Button::isRightClicked()
    {
        return is_right_clicked_;
    }
}