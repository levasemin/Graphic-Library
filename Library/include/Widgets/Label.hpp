#pragma once
#include "../Event/Ev.hpp"
#include "../BaseWidget/BaseWidget.hpp"
#include "../Options/Text.hpp"

namespace SL
{
    class Label : public Object
    {
    public:

        bool is_left_clicked_  = false;
        bool is_right_clicked_ = false;
        
        Text text_;
        int alignment_ = 0;

        enum Alignment
        {
            CenterCenter,
            LeftCenter,
            RightCenter,
            LeftUp,
            LeftDown,
            RightUp,
            RightDown
        };

        Label(Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::White));
        
        Label(const Label &source);

        Label &operator=(const Label &source);

        void setAlignment(int type);

        virtual void setString(const std::string &string);

        std::string getString();

        void setCharacterSize(int text_size);

        void setTextColor(const Color &color);

        void redraw();
    };
}