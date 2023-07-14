#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "Command.hpp"
#include "Event.hpp"
#include "Object.hpp"
#include "Text.hpp"

namespace SL
{
    class Button : public Object
    {
    public:

        bool is_left_clicked_  = false;
        bool is_right_clicked_ = false;
        bool is_pressed_       = false;

        bool is_press_button_ = false;

        Color default_sprite_color_;
        Text text_;
        
        Button(Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::White));
        Button(const Button& source);
        
        Button &operator=(const Button &source);

        void setTextColor(const Color &color);

        void setCharacterSize(int text_size);

        void set_pressed(bool is_press_button);

        void set_left_click           (Command<const Event &> *command);
        void set_release_left_click   (Command<const Event &> *command);
        void set_right_click          (Command<const Event &> *command);
        void set_release_right_click  (Command<const Event &> *command);
        
        
        Command<const Event &> * get_left_click ();
        Command<const Event &> * get_release_left_click ();
        Command<const Event &> * get_right_click ();
        Command<const Event &> * set_release_right_click ();

        void set_click_color(const Color &color);

        void set_texture(const Texture &texture) override;
        
        void setString(const std::string &text);

        void set_text(const Text &text);

        void ClickLeftEvent     (const Event &event) override;
        void ReleasedLeftEvent  (const Event &event) override;

        void ClickRightEvent    (const Event &event) override;
        void ReleasedRightEvent (const Event &event) override;
        
        void MoveMouseEvent     (const Event &event) override;

    protected:
        Command<const Event &> *left_click_command_    = nullptr;
        Command<const Event &> *left_release_command_  = nullptr;

        Command<const Event &> *right_click_command_   = nullptr;
        Command<const Event &> *right_release_command_ = nullptr;
    };
}