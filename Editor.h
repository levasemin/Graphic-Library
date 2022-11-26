#pragma once
#include "Label.h"

class Editor : public Label 
{
    Command<std::string> *editor_command_ = nullptr;

public:
    bool clicked_ = false;
    
    Editor(Vector2d shape, Vector2d center) : Label(shape, center)
    {
        std::string string = text_.getString();
    }

    void set_editor_command(Command<std::string> *editor_command)
    {
        editor_command_ = editor_command;
    }

    void setFont(const Font &font)
    {
        text_.setFont(font);
    }

    void PressKeyEvent (const Event &event) override
    {
        if (clicked_)
        {
            std::string string = text_.getString();

            if (event.Oleg_.kpedata.code == Key::Backspace)
            {
                if (string.size() > 0)
                {
                    string.pop_back();
                }
            }

            else
            {
                char letter = 0;

                if (Key::A <= event.Oleg_.kpedata.code && event.Oleg_.kpedata.code <= Key::Z)
                {
                    letter = (event.Oleg_.kpedata.shift ? event.Oleg_.kpedata.code + 'A' : event.Oleg_.kpedata.code + 'a');
                }

                else if (Key::Num0 <= event.Oleg_.kpedata.code && event.Oleg_.kpedata.code <= Key::Num9)    
                {
                    letter = event.Oleg_.kpedata.code - Key::Num0 + '0';
                }

                else if (Key::Numpad0 <= event.Oleg_.kpedata.code && event.Oleg_.kpedata.code <= Key::Numpad9)
                {
                    letter = event.Oleg_.kpedata.code - Key::Numpad0 + '0';
                }

                string.push_back(letter);
            }
            
            setString(string);

            if (editor_command_)
            {
                editor_command_->Execute(string);
            }
        }
    }

    void ClickLeftEvent(const Event &event) override
    {
        if (point_belonging(Vector2d(event.Oleg_.mbedata.x, event.Oleg_.mbedata.y)))
        {
            clicked_ = true;
        }

        else
        {
            clicked_ = false;
        }
    }

};