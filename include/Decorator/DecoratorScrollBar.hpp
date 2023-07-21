#pragma once

#include "Decorator.hpp"
#include "../Rendering/Rendering.hpp"
#include "../Widgets/Widgets.hpp"

namespace SL
{
    class DecoratorScrollBar : public CompositeObject
    {
    public:
        DecoratorScrollBar(Widget *widget, Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::White));

        DecoratorScrollBar(const DecoratorScrollBar &source) = default;
        DecoratorScrollBar &operator=(const DecoratorScrollBar &source) = default;
        ~DecoratorScrollBar();


        Widget *getWidget();
        void setWidget(Widget *widget);

        Vector2d getDecoratorShape() const;
        void setDecoratorShape (Vector2d shape);

        Vector2d getDecoratorPosition() const;
        void setDecoratorPosition(Vector2d position);


        void add (Widget *child)                 override;

        void remove (Widget *child)              override;

        Vector2d getPosition () const            override;
        void setPosition (Vector2d position)     override;

        Vector2d getShape () const               override;
        void setShape (Vector2d shape)           override;

        Texture getTexture () const              override;
        void setTexture (const Texture &texture) override;

    protected:
        void draw();
        virtual void display (Window *window) override;
        
        void setParent (Widget *parent) override;

        void clickLeftEvent (const Event &event) override;

        void releaseLeftEvent (const Event &event) override;           

        void moveMouseEvent (const Event &event) override;

        void scrollEvent(const Event &event) override;
    
    private:
        Widget *widget_;

        bool scroll_bar_horizontal_able_ = true;
        bool scroll_bar_vertical_able_   = true;

        Vector2d current_value_;  
        Vector2d scroll_shape_;

        VerticalScrollBar scroll_bar_vertical_;
        HorizontalScrollBar scroll_bar_horizontal_;

        void ScrollVerticalWidget(const Event &event);
        void ScrollHorizontalWidget(const Event &event);
    };
}