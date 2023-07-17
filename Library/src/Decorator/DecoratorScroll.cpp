#include "DecoratorScroll.hpp"

namespace SL
{
    DecoratorScroll::DecoratorScroll(Widget *widget) : Decorator(widget)
    {}

    void DecoratorScroll::scrollEvent (const Event &event)
    {
        if (pointBelong(event.Oleg_.sedata.pos))
        {
            setLocalOffset(Vector2d(0.f, getLocalOffset().y_ + event.Oleg_.sedata.value * 10.f));   
        }
    }

    void DecoratorScroll::setLocalOffset(Vector2d offset)
    {       
        offset.x_ = offset.x_ <= 0 ? offset.x_ : 0;
        offset.y_ = offset.y_ <= 0 ? offset.y_ : 0;
        
        Vector2d max_offset = getShape() - getGlobalShape();
        
        if (max_offset.x_ < 0)
        {
            offset.x_ = offset.x_ >= max_offset.x_ ? offset.x_ : max_offset.x_;
        }

        if (max_offset.y_ < 0)
        {
            offset.y_ = offset.y_ >= max_offset.y_ ? offset.y_ : max_offset.y_;
        }
        
        Decorator::setLocalOffset(offset);
    }

    void DecoratorScroll::add(Widget *widget)
    {
        widget_->add(widget);
    }
}