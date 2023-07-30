#pragma once

#include "CompositeObject.hpp"
#include "VerticalScrollBar.hpp"
#include "HorizontalScrollBar.hpp"
#include "Container.hpp"

namespace SL
{
    class DecoratorScrollBar : public CompositeObject
    {
    public:
        DecoratorScrollBar(Widget *widget, Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::White));

        DecoratorScrollBar (const DecoratorScrollBar &source);
        DecoratorScrollBar &operator=(const DecoratorScrollBar &source);
        ~DecoratorScrollBar();

        Widget *getWidget();
        void setWidget(Widget *widget);

        void add (Widget *child)                 override;

        void remove (Widget *child)              override;

    protected:        
        void scrollEvent(const Event &event) override;
    
    private:
        Widget *widget_;

        bool scroll_bar_horizontal_able_ = true;
        bool scroll_bar_vertical_able_   = true;

        Vector2d current_value_;  
        Vector2d scroll_shape_;

        VerticalScrollBar scroll_bar_vertical_;
        HorizontalScrollBar scroll_bar_horizontal_;
        Container scroll_container_;

        void ScrollVerticalWidget(float value);
        void ScrollHorizontalWidget(float value);
    };
}