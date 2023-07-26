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
    public:
        HorizontalScrollBar(Vector2d shape, Vector2d position, float min_value, float max_value, const Texture &texture = Texture(Color::White));

        HorizontalScrollBar(const HorizontalScrollBar &source);
        HorizontalScrollBar &operator=(const HorizontalScrollBar &source); 
        ~HorizontalScrollBar() override;

        float getValue ();
        void  setValue (float value_);

        float getMinValue ();
        void  setMinValue (float min_value);
        
        float getMaxValue ();
        void  setMaxValue (float max_value);

        void setSideButton (bool able);

        void setScrollButtonShape (const Vector2d &shape);

        Command<float> *getScrollCommand();
        void setScrollCommand (Command<float> *new_command);

    protected:
        void moveMouseEvent (const Event &event) override;
        
        void clickLeftEvent (const Event &event) override;
    
    private:
        Button left_button_;
        Button right_button_;    
        Button scroll_button_;

        Vector2d click_place_;
        Vector2d scroll_field_shape_;

        float min_value_;
        float max_value_;
        float scroll_coeff_ = SCROLL_COEFF;
        
        bool is_scroll_surface_click_ = true;

        Command<float> *scroll_command_ = nullptr;

        Texture scroll_button_texture_;

        void scrollUp ();   

        void scrollDown ();

        void clickedScrollButton ();
    };
}