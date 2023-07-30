#pragma once

#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "CompositeObject.hpp"

namespace SL
{
    class DecoratorScroll : public CompositeObject
    {
    public :
        DecoratorScroll(Widget *widget, Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::White));
        
        DecoratorScroll(const DecoratorScroll &source);
        DecoratorScroll &operator=(const DecoratorScroll &source);
        DecoratorScroll(DecoratorScroll &&source);
        DecoratorScroll &operator=(DecoratorScroll &&source);
        ~DecoratorScroll();
    
        Widget *getWidget();
        void setWidget(Widget *widget);

        void add (Widget *child)                 override;

        void remove (Widget *child)              override;
        
    protected:
        void scrollEvent (const Event &event) override;

    private:
        Widget *widget_;

        float offset_;
        float scroll_shape_;
    };
}