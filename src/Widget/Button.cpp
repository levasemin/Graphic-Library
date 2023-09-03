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

    Texture Button::getTexture() const
    {
        if (getColor() == default_sprite_color_)
        {
            return Label::getTexture();
        }
        else
        {
            Sprite sprite(getShape(), Label::getTexture());
            sprite.setColor(default_sprite_color_);
            
            return sprite.getTexture();
        }
    }

    void Button::setTexture(const Texture &texture)
    {
        if (getColor() != default_sprite_color_)
        {
            Label::setTexture(texture);
            default_sprite_color_ = getColor();
            
            make_blackout();
        }

        else
        {
            Label::setTexture(texture);
            default_sprite_color_ = getColor();
        }
    }

    void Button::clickEvent (const Event &event)
    {   
        if (pointBelong(event.Oleg_.mpedata.pos))
        {
            if (event.Oleg_.mpedata.button == Event::MouseButton::Left)
            {
                is_left_clicked_ = true;

                if (left_click_command_ != nullptr)
                {
                    left_click_command_->Execute();
                }
            }

            else
            {
                is_right_clicked_ = true;

                if (right_click_command_ != nullptr)
                {
                    right_click_command_->Execute();
                }
            }
        }
    }

    void Button::releaseEvent (const Event &event)
    {
        if (event.Oleg_.mredata.button == Event::MouseButton::Left)
        {
            if (left_release_command_ != nullptr)
            {
                left_release_command_->Execute();
            }
    
            is_left_clicked_ = false;
        }

        else
        {
            if (right_release_command_ != nullptr)
            {
                right_release_command_->Execute();
            }

            is_right_clicked_ = false;
        }
    }

    void Button::moveMouseEvent(const Event &event)
    {        
        if (pointBelong(event.Oleg_.metion.pos))
        {
            make_blackout();
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
            make_blackout();
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

    void Button::make_blackout()
    {
        Color new_color = default_sprite_color_;
        
        new_color.set_v(new_color.get_v() / 3 * 2);

        setColor(new_color);
    }
}