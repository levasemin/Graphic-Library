#pragma once

#include "Decorator.hpp"
#include "../Rendering/Rendering.hpp"
#include "../Widgets/Widgets.hpp"

namespace SL
{
    class DecoratorScrollBar : public Decorator
    {
    public:
        DecoratorScrollBar(Widget *widget);

        DecoratorScrollBar(const DecoratorScrollBar &source) = default;
        DecoratorScrollBar &operator=(const DecoratorScrollBar &source) = default;
        ~DecoratorScrollBar();

        void draw() override;

        void display(Window *window) override;

        void setParent(Widget *parent_widget) override;


        void clickLeftEvent (const Event &event) override;

        void releaseLeftEvent (const Event &event) override;           

        void moveMouseEvent (const Event &event) override;

        void scrollEvent(const Event &event) override;

        void ScrollVerticalWidget(const Event &event);

        void ScrollHorizontalWidget(const Event &event);
    
    protected:
        VerticalScrollBar scroll_bar_vertical_;
        HorizontalScrollBar scroll_bar_horizontal_;
    
    private:
        bool scroll_bar_horizontal_able_ = true;
        bool scroll_bar_vertical_able_   = true;

        Vector2d current_value_;  

        float sum;
    };
}