#pragma once

#include "Decorator.hpp"
#include "../Rendering/Rendering.hpp"
#include "../Widgets/Widgets.hpp"

namespace SL
{
    class DecoratorScrollBar : public Decorator
    {
    protected:
        VerticalScrollBar scroll_bar_vertical_;
        HorizontalScrollBar scroll_bar_horizontal_;

        bool scroll_bar_horizontal_able_ = true;
        bool scroll_bar_vertical_able_   = true;
        
    public:
        DecoratorScrollBar(Widget *widget);

        void scrollEvent(const Event &event) override;

        void ScrollVerticalWidget(const Event &event);

        void ScrollHorizontalWidget(const Event &event);

        void draw() override;

        void clickLeftEvent (const Event &event) override;

        void releaseLeftEvent (const Event &event) override;           
        
        void moveMouseEvent (const Event &event) override;

        void setGlobalOffset(Vector2d offset) override;

        void display(Window *window) override;

        void setParent(Widget *parent_widget) override;
    };
}