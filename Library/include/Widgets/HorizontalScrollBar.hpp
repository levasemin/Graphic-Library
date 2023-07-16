#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#pragma once

#include "../Rendering/Rendering.hpp"
#include "../BaseWidget/BaseWidget.hpp"
#include "../Event/Ev.hpp"
#include "../Classes/Classes.hpp"
#include "Button.hpp"

namespace SL
{
    class HorizontalScrollBar : public CompositeObject
    {
    protected:
        Button left_button_;
        Button right_button_;    
        Button scroll_button_;
        Vector2d scroll_field_shape;
        float min_value_;
        float max_value_;

    public:
        Command<const Event&> *scroll_command_ = nullptr;

        float scroll_coeff_ = SCROLL_COEFF;
        
        Vector2d click_place_;
        
        HorizontalScrollBar(Vector2d shape, Vector2d position, float min_value, float max_value);

        HorizontalScrollBar(const HorizontalScrollBar &source);

        HorizontalScrollBar &operator=(const HorizontalScrollBar &source);

        void set_button(bool able);

        void set_scroll_button_shape(const Vector2d &shape);

        void set_up_right_button_shape(const Vector2d &shape);

        virtual void scroll_bar(float value_);   

        void MoveMouseEvent (const Event &event) override;

        void scroll_up(const Event &event);   

        void scroll_down(const Event &event);
        
        void ClickLeftEvent(const Event &event) override;

        void clicked_scroll_button(const Event &event);

        void set_scroll_command(Command<const Event &> *new_command);

        ~HorizontalScrollBar() override {}
    };
}