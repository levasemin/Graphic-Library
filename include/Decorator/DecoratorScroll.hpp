#pragma once

#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "../BaseWidget/CompositeObject.hpp"

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

        Vector2d getDecoratorShape() const;
        void setDecoratorShape (Vector2d shape);

        Vector2d getDecoratorPosition() const;
        void setDecoratorPosition(Vector2d position);



        void add (Widget *child)                 override;

        void remove (Widget *child)              override;

        Vector2d getPosition() const override;
        void setPosition(Vector2d position) override;

        Vector2d getShape() const override;
        void setShape (Vector2d shape) override;

        Texture getTexture () const              override;
        void setTexture (const Texture &texture) override;
        
    protected:
        void scrollEvent (const Event &event) override;

    private:
        Widget *widget_;

        float offset_;
        float scroll_shape_;
    };
}