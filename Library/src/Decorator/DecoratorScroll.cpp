#include "DecoratorScroll.hpp"

namespace SL
{
    DecoratorScroll::DecoratorScroll(Widget *widget) : Decorator(widget)
    {}

    void DecoratorScroll::ScrollEvent (const Event &event)
    {
        if (point_belonging(event.Oleg_.sedata.pos))
        {
            set_local_offset(Vector2d(0.f, get_local_offset().y_ + event.Oleg_.sedata.value * 10.f));   
        }
    }

    void DecoratorScroll::set_local_offset(Vector2d offset)
    {       
        offset.x_ = offset.x_ <= 0 ? offset.x_ : 0;
        offset.y_ = offset.y_ <= 0 ? offset.y_ : 0;
        
        Vector2d max_offset = get_shape() - get_global_shape();
        
        if (max_offset.x_ < 0)
        {
            offset.x_ = offset.x_ >= max_offset.x_ ? offset.x_ : max_offset.x_;
        }

        if (max_offset.y_ < 0)
        {
            offset.y_ = offset.y_ >= max_offset.y_ ? offset.y_ : max_offset.y_;
        }
        
        Decorator::set_local_offset(offset);
    }

    void DecoratorScroll::add(Widget *widget)
    {
        widget_->add(widget);
    }
}