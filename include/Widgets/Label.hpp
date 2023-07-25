#pragma once
#include "../Event/Ev.hpp"
#include "../BaseWidget/BaseWidget.hpp"
#include "../Options/Text.hpp"

namespace SL
{
    class Label : public Object
    {
    public:

        enum class Alignment
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
        
        Label(const Label &source) = default;
        Label &operator=(const Label &source) = default;
        ~Label() = default;

        void setText(const Text &text);
        void setText(const std::string &string);

        std::string getText();
        
        void setAlignment(Alignment type);

        void setCharacterSize(int text_size);

        void setTextColor(const Color &color);

    private:        
        Text text_;
        Alignment alignment_ = Alignment::CenterCenter;

        void redraw();
    };
}