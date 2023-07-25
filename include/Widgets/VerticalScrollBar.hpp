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
        
        VerticalScrollBar(Vector2d shape, Vector2d position, float min_value, float max_value, const Texture &texture = Texture(Color::White));

        VerticalScrollBar(const VerticalScrollBar &source);
        VerticalScrollBar &operator =(const VerticalScrollBar &source);
        ~VerticalScrollBar();

        float getValue ();
        void  setValue (float value);
        
        float getMinValue ();
        void  setMinValue (float min_value);
        
        float getMaxValue ();
        void  setMaxValue (float max_value);

        void setSideButton(bool able);

        void setScrollButtonShape(const Vector2d &shape);

        Command<const Event &> *getScrollCommand();
        void setScrollCommand(Command<const Event &> *new_command);
    
    protected:
        void moveMouseEvent (const Event &event) override;

        void clickLeftEvent(const Event &event) override;

        void scrollEvent(const Event &event) override;

    private:
        Button up_button_;
        Button down_button_;    
        Button scroll_button_;

        Vector2d click_place_;
        Vector2d scroll_field_shape_;
        
        float min_value_;
        float max_value_;
        float scroll_coeff_ = SCROLL_COEFF;
    
        bool is_scroll_surface_click_ = true;

        Command<const Event&> *scroll_command_ = nullptr;

        Texture scroll_button_texture_;

        void scrollUp(const Event &event);

        void scrollDown(const Event &event);

        void clickedScrollButton(const Event &event);
    };
}