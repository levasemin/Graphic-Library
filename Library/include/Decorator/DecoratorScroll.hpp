#pragma once

#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "Decorator.hpp"

namespace SL
{
    class DecoratorScroll : public Decorator
    {

    public :
        DecoratorScroll(Widget *widget);

        void ScrollEvent (const Event &event) override;

        void set_local_offset(Vector2d offset) override;

        void add(Widget *widget) override;
    };
}