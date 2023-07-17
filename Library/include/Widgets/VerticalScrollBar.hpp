#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "../Rendering/Rendering.hpp"
#include "../BaseWidget/BaseWidget.hpp"
#include "../Event/Ev.hpp"
#include "Button.hpp"
#include "../Classes/constants.hpp"

namespace SL
{
    class VerticalScrollBar : public CompositeObject
    {
    public:
        
        float scroll_coeff_ = SCROLL_COEFF;
        
        Vector2d click_place_;
        
        Button up_button_;
        Button down_button_;    
        Button scroll_button_;
        Vector2d scroll_field_shape;
        float min_value_ = 0;
        float max_value_ = 1;

        Command<const Event&> *scroll_command_ = nullptr;
        
        VerticalScrollBar(Vector2d shape, Vector2d position, float min_value, float max_value);

        VerticalScrollBar(const VerticalScrollBar &source);

        VerticalScrollBar &operator =(const VerticalScrollBar &source);
        
        ~VerticalScrollBar();

        void set_button(bool able);

        void set_scroll_button_size(const Vector2d &shape);


        void scrollEvent(const Event &event) override;
    
        void scroll_bar(float value_);

        void moveMouseEvent (const Event &event) override;

        void scroll_up(const Event &event);

        void scroll_down(const Event &event);
        
        void clickLeftEvent(const Event &event) override;

        void clicked_scroll_button(const Event &event);

        void set_scroll_command(Command<const Event &> *new_command);
    };
}