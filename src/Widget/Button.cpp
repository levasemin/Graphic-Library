#include "Button.hpp"

namespace SL
{
    Button::Button(Vector2d shape, Vector2d position, const Texture &texture) : Label(shape, position, texture), 
        default_sprite_color_(getColor())
    {
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