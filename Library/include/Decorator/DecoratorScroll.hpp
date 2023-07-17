#pragma once

#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "Decorator.hpp"

namespace SL
{
    class DecoratorScroll : public Decorator
    {

    public :
        DecoratorScroll(Widget *widget);

        void scrollEvent (const Event &event) override;

        void setLocalOffset(Vector2d offset) override;

        void add(Widget *widget) override;
    };
}