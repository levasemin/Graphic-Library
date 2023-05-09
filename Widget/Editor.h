#pragma once
#pragma GCC diagnostic ignored "-Wswitch-enum"

#include "Label.h"

namespace SL
{
    class Editor : public Label 
    {
    protected:
        Color default_sprite_color_;
        Command<const Event &> *editor_command_ = nullptr;

    public:
        bool clicked_ = false;
        size_t current_pos_ = 0;

        Editor(Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::White)) : Label(shape, position, texture),
            default_sprite_color_(sprite_.getColor())
        {
            std::string string = text_.getString();
        }

        Editor(const Editor &source): Label(*(const Label *)&source),    
            default_sprite_color_(source.default_sprite_color_),
            editor_command_(source.editor_command_)
        {}
        Editor &operator=(const Editor &source)
        {
            Label::operator=(*(const Label *)&source);
            default_sprite_color_ = source.default_sprite_color_;
            editor_command_ = source.editor_command_;

            return *this;
        }

        void set_texture(const Texture &texture) override
        {
            Object::set_texture(texture);
            default_sprite_color_ = sprite_.getColor();
        }

        void set_editor_command(Command<const Event &> *editor_command)
        {
            editor_command_ = editor_command;
        }

        void setFont(const Font &font)
        {
            text_.setFont(font);
        }

        std::string get_text()
        {
            std::string text = text_.getString();
            text.erase(text.begin() + current_pos_);

            return text;
        }

        void PressKeyEvent (const Event &event) override
        {
            if (clicked_)
            {
                std::string string = text_.getString();

                switch (event.Oleg_.kpedata.code)
                {
                    case Key::Backspace:
                    {
                        if (current_pos_ > 0)
                        {
                            string.erase(string.begin() + current_pos_);
                            string.erase(string.begin() + current_pos_ - 1);
                            current_pos_ --;
                        }

                        break;
                    }

                    case Key::Left:
                    {
                        if (current_pos_ > 0)
                        {
                            string.erase(string.begin() + current_pos_);

                            current_pos_ --;
                        }

                        break;
                    }

                    case Key::Right:
                    {
                        if (current_pos_ + 1 < string.size())
                        {
                            string.erase(string.begin() + current_pos_);

                            current_pos_ ++;
                        }

                        break;
                    }

                    default:
                    {}
                };
                
                setString(string);

                if (editor_command_)
                {                
                    Event new_event = event;
                    std::string final_string = get_text();
                    new_event.Oleg_.textedata.text = final_string.c_str();
                    editor_command_->Execute(new_event);
                }
            }
        }
        
        void TextEvent(const Event &event) override
        {
            if (clicked_)
            {
                std::string string = text_.getString();

                if (current_pos_ > 0)
                {
                    string.erase(string.begin() + current_pos_);
                }

                char letter = event.Oleg_.textedata.letter;

                string.insert(string.begin() + current_pos_, letter);
                current_pos_ ++;
                setString(string);

                if (editor_command_)
                {
                    std::string final_string = get_text();
                    Event new_event = event;
                    new_event.Oleg_.textedata.text = final_string.c_str();
                    editor_command_->Execute(new_event);
                }
            }
        }

        void MoveMouseEvent(const Event &event) override
        {
            if (point_belonging(event.Oleg_.motion.pos))
            {
                Color new_color = default_sprite_color_;
            
                new_color /= 3;
                new_color *= 2;

                sprite_.setColor(new_color);
            }

            else if (!clicked_) 
            {
                sprite_.setColor(default_sprite_color_);
            }

            Label::MoveMouseEvent(event);
        }

        void ClickLeftEvent(const Event &event) override
        {
            if (point_belonging(event.Oleg_.mbedata.pos))
            {
                clicked_ = true;

                Color new_color = default_sprite_color_;
                new_color /= 3;
                new_color *= 2;

                sprite_.setColor(new_color);

                std::string string = text_.getString();

                current_pos_ = string.size();
                setString(string);
            }

            else
            {
                if (clicked_ == true)
                {
                    std::string string = text_.getString();
                    string.erase(string.begin() + current_pos_);
        
                    clicked_ = false;

                    setString(string);
                }

                sprite_.setColor(default_sprite_color_);
            }
        }

        void setString(const std::string &string) override
        {
            std::string final_string = string;
            if (clicked_)
            {
                if (final_string.find('|') == std::string::npos)
                {
                    current_pos_ = current_pos_ < final_string.size() ? current_pos_ : final_string.size();
                    final_string.insert(final_string.begin() + current_pos_, '|');
                }
            }
            
            Label::setString(final_string);
        }
    };  
}