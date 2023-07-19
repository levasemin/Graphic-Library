#pragma once

#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "Decorator.hpp"

namespace SL
{
    class DecoratorScroll : public Decorator
    {

    public :
        DecoratorScroll(Widget *widget);
        
        void add(Widget *widget) override;

        void scrollEvent (const Event &event) override;
    };
}