#include "Button.hpp"

namespace SL
{
    Button::Button(Vector2d shape, Vector2d position, const Texture &texture) : Object(shape, position, texture), 
        default_sprite_color_(sprite_.getColor()),
        text_()
    {
        text_.setFont(Font::Times_new_roman);
    };

    Command<const Event &>* Button::getLeftClick ()
    {
        return left_click_command_;
    }
    void Button::setLeftClick (Command<const Event &>* command)
    {
        left_click_command_ = command;
    }
    
    Command<const Event &>* Button::getReleaseLeftClick ()
    {
        return left_release_command_;
    }
    void Button::setReleaseLeftClick (Command<const Event &>* command)
    {
        left_release_command_ = command;
    }
    
    Command<const Event &>* Button::getRightClick ()
    {
        return right_click_command_;
    }
    void Button::setRightClick (Command<const Event &>* command)
    {
        right_click_command_ = command;
    }
    
    Command<const Event &>* Button::getReleaseRightClick ()
    {
        return right_release_command_;
    }
    void Button::setReleaseRightClick (Command<const Event &>* command)
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
        text_ = text;
        sprite_.setTexture(texture_);
        render_texture_.draw(sprite_);

        Vector2d text_position(0, 0);
        text_position.x_ = shape_.x_ / 2 - text_.getGlobalBounds().x_ / 2;
        text_position.y_ = shape_.y_ / 2 - text_.getGlobalBounds().y_; 
        text_.setPosition(text_position);

        render_texture_.draw(text_); 
    }

    void Button::setTexture(const Texture &texture)
    {
        Object::setTexture(texture);
        default_sprite_color_ = sprite_.getColor();
    }

    void Button::clickLeftEvent (const Event &event)
    {   
        if (pointBelong(Vector2d(event.Oleg_.mbedata.pos)))
        {
            is_left_clicked_ = true;

            if (left_click_command_ != nullptr)
            {
                Event new_event;
                new_event.type_ = EventType::ButtonClicked;
                new_event.Oleg_.bcedata.id = (uint64_t)this;
                left_click_command_->Execute(new_event);
            }
        }
    }

    void Button::releaseLeftEvent (const Event &event)
    {
        if (left_release_command_ != nullptr)
        {
            left_release_command_->Execute(event);
        }

        is_left_clicked_ = false;
    }

    void Button::clickRightEvent (const Event &event)
    {
        if (pointBelong(event.Oleg_.mbedata.pos))
        {
            is_right_clicked_ = true;

            if (right_click_command_ != nullptr)
            {
                Event new_event;
                new_event.type_ = EventType::ButtonClicked;
                new_event.Oleg_.bcedata.id = (uint64_t)this;
                right_click_command_->Execute(new_event);
            }
        }
    }

    void Button::releaseRightEvent (const Event &event)
    {
        if (right_release_command_ != nullptr)
        {
            right_release_command_->Execute(event);
        }

        is_right_clicked_ = false;
    }

    void Button::moveMouseEvent(const Event &event)
    {        
        if (pointBelong(event.Oleg_.motion.pos))
        {
            Color new_color = default_sprite_color_;
        
            new_color.set_a(uint8_t(new_color.get_a() / 3 * 2));

            sprite_.setColor(new_color);
        }

        else
        {
            sprite_.setColor(default_sprite_color_);
        }   
    }

    void Button::scrollEvent(const Event &event)
    {
        if (pointBelong(event.Oleg_.sedata.pos))
        {
            Color new_color = default_sprite_color_;
        
            new_color.set_a(uint8_t(new_color.get_a() / 3 * 2));

            sprite_.setColor(new_color);
        }

        else
        {
            sprite_.setColor(default_sprite_color_);
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