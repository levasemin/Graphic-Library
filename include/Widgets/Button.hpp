#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "Label.hpp"
#include "Command.hpp"
#include "Event.hpp"
#include "Text.hpp"

namespace SL
{
    class Button : public Label
    {
    public:
        Button(Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::White));
        
        Button (const Button& source) = default;
        Button &operator= (const Button &source) = default;
        ~Button () = default; 
        
        bool isLeftClicked();
        bool isRightClicked();
        
        Command<> *getLeftClick ();
        void setLeftClick (Command<> *command);

        Command<> *getReleaseLeftClick ();
        void setReleaseLeftClick (Command<> *command);

        Command<> *getRightClick ();
        void setRightClick (Command<> *command);

        Command<> *getReleaseRightClick ();
        void setReleaseRightClick (Command<> *command);

        Texture getTexture() const override;
        void setTexture(const Texture &texture) override;
        
    protected:
        void moveMouseEvent    (const Event &event) override;

        void pressEvent    (const Event &event) override;
        void releaseEvent  (const Event &event) override;
        
        void scrollEvent        (const Event &event) override;

    private:
        bool is_left_clicked_  = false;
        bool is_right_clicked_ = false;

        Color default_sprite_color_;

        Command<> *left_click_command_    = nullptr;
        Command<> *left_release_command_  = nullptr;

        Command<> *right_click_command_   = nullptr;
        Command<> *right_release_command_ = nullptr;

        void make_blackout();
    };
}