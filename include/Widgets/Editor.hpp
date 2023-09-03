#pragma once
#pragma GCC diagnostic ignored "-Wswitch-enum"

#include "Label.hpp"

namespace SL
{
    class Editor : public Label 
    {
    public:
        Editor(Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::White));
        
        Editor(const Editor &source) = default;
        Editor &operator=(const Editor &source) = default;
        ~Editor() = default;

        void setText(const std::string &string);
        void setText(const Text &text);
        
        std::string getText();

        Command<std::string> * getEditorCommand();
        void setEditorCommand(Command<std::string> *editor_command);

        Texture getTexture() const override;
        void setTexture(const Texture &texture) override;

    protected:
        void moveMouseEvent(const Event &event) override;

        void clickEvent(const Event &event) override;

        void pressKeyEvent (const Event &event) override;
        
        void scrollEvent(const Event &event) override;
        
        void textEvent(const Event &event) override;

    private:
        bool clicked_ = false;
        size_t cursor_pos_ = 0;
        
        Color default_sprite_color_;

        Command<std::string> *editor_command_ = nullptr;

        void make_blackout();
    };
}