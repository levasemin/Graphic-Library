#include "Editor.hpp"

namespace SL
{
    Editor::Editor(Vector2d shape, Vector2d position, const Texture &texture) : Label(shape, position, texture),
            default_sprite_color_(getColor())
    {
    }

    void Editor::setTexture(const Texture &texture)
    {
        Object::setTexture(texture);
        default_sprite_color_ = getColor();
    }

    void Editor::setEditorCommand(Command<const Event &> *editor_command)
    {
        editor_command_ = editor_command;
    }

    Command<const Event &> *Editor::getEditorCommand()
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
                case Key::Backspace:
                {
                    if (cursor_pos_ > 0)
                    {
                        string.erase(string.begin() + cursor_pos_ - 1);
                        cursor_pos_ --;
                    }

                    break;
                }

                case Key::Left:
                {
                    if (cursor_pos_ > 0)
                    {
                        cursor_pos_ --;
                    }

                    break;
                }

                case Key::Right:
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
                Event new_event = event;
                std::string final_string = getText();
                new_event.Oleg_.textedata.text = final_string.c_str();
                editor_command_->Execute(new_event);
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

            char letter = event.Oleg_.textedata.letter;

            string.insert(string.begin() + cursor_pos_, letter);
            cursor_pos_ ++;
            setText(string);

            if (editor_command_)
            {
                std::string final_string = getText();
                Event new_event = event;
                new_event.Oleg_.textedata.text = final_string.c_str();
                editor_command_->Execute(new_event);
            }
        }
    }

    void Editor::moveMouseEvent(const Event &event)
    {
        if (pointBelong(event.Oleg_.motion.pos))
        {
            Color new_color = default_sprite_color_;
            new_color.set_h(new_color.get_h() / 3.f * 2.f);
            setColor(new_color);
        }

        else if (!clicked_) 
        {
            setColor(default_sprite_color_);
        }

        Label::moveMouseEvent(event);
    }

    void Editor::clickLeftEvent(const Event &event)
    {
        if (pointBelong(event.Oleg_.mbedata.pos))
        {
            clicked_ = true;

            Color new_color = default_sprite_color_;
            new_color.set_h(new_color.get_h() / 3.f * 2.f);
            setColor(new_color);

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
}