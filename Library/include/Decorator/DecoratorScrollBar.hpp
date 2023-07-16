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

        void ScrollEvent(const Event &event) override;

        void ScrollVerticalWidget(const Event &event);

        void ScrollHorizontalWidget(const Event &event);

        void draw() override;

        void ClickLeftEvent (const Event &event) override;

        void ReleasedLeftEvent (const Event &event) override;           
        
        void MoveMouseEvent (const Event &event) override;

        void set_global_offset(Vector2d offset) override;

        void display(Window *window) override;

        void set_parent(Widget *parent_widget) override;
    };
}