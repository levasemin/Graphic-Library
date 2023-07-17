#pragma once
#pragma GCC diagnostic ignored "-Wswitch-enum"

#include "Label.hpp"

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

        Editor(Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::White));
        Editor(const Editor &source);
        Editor &operator=(const Editor &source);

        void setTexture(const Texture &texture) override;
        void set_editor_command(Command<const Event &> *editor_command);
        void setFont(const Font &font);

        std::string get_text();

        void pressKeyEvent (const Event &event) override;
        
        void textEvent(const Event &event) override;

        void moveMouseEvent(const Event &event) override;

        void clickLeftEvent(const Event &event) override;

        void setString(const std::string &string) override;
    };  
}