#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "../Event/Ev.hpp"
#include "../BaseWidget/Object.hpp"
#include "../Options/Text.hpp"

namespace SL
{
    class Button : public Object
    {
    public:
        Button(Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::White));
        
        Button (const Button& source) = default;
        Button &operator= (const Button &source) = default;
        ~Button () = default; 

        Command<const Event &> * getLeftClick ();
        void setLeftClick (Command<const Event &> *command);

        Command<const Event &> * getReleaseLeftClick ();
        void setReleaseLeftClick (Command<const Event &> *command);

        Command<const Event &> * getRightClick ();
        void setRightClick (Command<const Event &> *command);

        Command<const Event &> * getReleaseRightClick ();
        void setReleaseRightClick (Command<const Event &> *command);

        void setText(const std::string &text);

        void setTextColor(const Color &color);

        void setCharacterSize(int text_size);


        void setText(const Text &text);

        void setClickTexture(const Texture &texture);

        void setTexture(const Texture &texture) override;
    

        void clickLeftEvent    (const Event &event) override;
        void releaseLeftEvent  (const Event &event) override;

        void clickRightEvent   (const Event &event) override;
        void releaseRightEvent (const Event &event) override;
        
        void moveMouseEvent    (const Event &event) override;
        
        void scrollEvent        (const Event &event) override;

        bool isLeftClicked();
        bool isRightClicked();

    private:
        bool is_left_clicked_  = false;
        bool is_right_clicked_ = false;

        Color default_sprite_color_;
        Text text_;

        Command<const Event &> *left_click_command_    = nullptr;
        Command<const Event &> *left_release_command_  = nullptr;

        Command<const Event &> *right_click_command_   = nullptr;
        Command<const Event &> *right_release_command_ = nullptr;
    };
}