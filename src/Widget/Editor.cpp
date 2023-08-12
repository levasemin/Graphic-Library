#include "Editor.hpp"

namespace SL
{
    Editor::Editor(Vector2d shape, Vector2d position, const Texture &texture) : Label(shape, position, texture),
            default_sprite_color_(getColor())
    {
    }

    Texture Editor::getTexture() const
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
    
    void Editor::setTexture(const Texture &texture)
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

    void Editor::setEditorCommand(Command<std::string> *editor_command)
    {
        editor_command_ = editor_command;
    }

    Command<std::string> *Editor::getEditorCommand()
    {
        return editor_command_;
    }
    
    std::string Editor::getText()
    {
        std::string text = Label::getText();
        
        if (clicked_)
        {
            text.erase(text.begin() + cursor_pos_);
        }

        return text;
    }

    void Editor::pressKeyEvent (const Event &event)
    {
        if (clicked_)
        {
            std::string string = Label::getText();

            string.erase(string.begin() + cursor_pos_);

            switch (event.Oleg_.kpedata.code)
            {
                case Event::Key::Backspace:
                {
                    if (cursor_pos_ > 0)
                    {
                        string.erase(string.begin() + cursor_pos_ - 1);
                        cursor_pos_ --;
                    }

                    break;
                }

                case Event::Key::Left:
                {
                    if (cursor_pos_ > 0)
                    {
                        cursor_pos_ --;
                    }

                    break;
                }

                case Event::Key::Right:
                {
                    if (cursor_pos_ < string.size())
                    {
                        cursor_pos_ ++;
                    }

                    break;
                }

                default:
                {}
            };
            
            
            setText(string);

            if (editor_command_)
            {                
                editor_command_->Execute(getText());
            }
        }
    }
    
    void Editor::textEvent(const Event &event)
    {
        if (clicked_)
        {
            std::string string = Label::getText();

            if (cursor_pos_ > 0)
            {
                string.erase(string.begin() + cursor_pos_);
            }

            char letter = event.Oleg_.tedata.letter;

            string.insert(string.begin() + cursor_pos_, letter);
            cursor_pos_ ++;
            setText(string);

            if (editor_command_)
            {
                editor_command_->Execute(getText());
            }
        }
    }

    void Editor::moveMouseEvent(const Event &event)
    {
        if (pointBelong(event.Oleg_.metion.pos))
        {
            make_blackout();
        }

        else if (!clicked_) 
        {
            setColor(default_sprite_color_);
        }

        Label::moveMouseEvent(event);
    }

    void Editor::scrollEvent(const Event &event)
    {
        if (pointBelong(event.Oleg_.mwsedata.pos))
        {
            make_blackout();
        }

        else if (!clicked_) 
        {
            setColor(default_sprite_color_);
        }

        Label::scrollEvent(event);
    }
    
    void Editor::clickLeftEvent(const Event &event)
    {
        if (pointBelong(event.Oleg_.mpedata.pos))
        {
            clicked_ = true;

            make_blackout();

            std::string string = Label::getText();

            cursor_pos_ = string.size();
            setText(string);
        }

        else
        {
            if (clicked_ == true)
            {
                std::string string = Label::getText();
                string.erase(string.begin() + cursor_pos_);
    
                clicked_ = false;
            }

            setColor(default_sprite_color_);
        }
    }

    void Editor::setText(const std::string &string)
    {
        std::string final_string = string;

        if (clicked_)
        {
            if (final_string.find('|') == std::string::npos)
            {
                cursor_pos_ = cursor_pos_ < final_string.size() ? cursor_pos_ : final_string.size();
                final_string.insert(final_string.begin() + cursor_pos_, '|');
            }
        }
        
        Label::setText(final_string);
    }

    void Editor::make_blackout()
    {
        Color new_color = default_sprite_color_;
        new_color.set_h(new_color.get_h() / 3.f * 2.f);
        setColor(new_color);
    }
}