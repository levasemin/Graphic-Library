#include "Decorator.h"

class DecoratorScroll : public Decorator
{
    Vector2d global_offset0_ = (0, 0);

public :
    DecoratorScroll(Widget *widget) : Decorator(widget)
    {
    }

    void ScrollEvent (const Event &event) override
    {
        if (point_belonging(Vector2d(event.Oleg_.sedata.x, event.Oleg_.sedata.y)))
        {
            set_local_offset(Vector2d(0, event.Oleg_.sedata.value));   
        }
    }

    void set_local_offset(Vector2d diff_offset) override
    {       
        if (diff_offset.y_ > 0)
        {
            diff_offset.x_ = diff_offset.x_ <= -global_offset0_.x_ ? diff_offset.x_ :  -global_offset0_.x_;
            diff_offset.y_ = diff_offset.y_ <= -global_offset0_.y_ ? diff_offset.y_ :  -global_offset0_.y_;
        }
        
        if (diff_offset.y_ < 0)
        {
            Vector2d max_offset =  global_offset0_ + widget_->get_global_shape() - widget_->get_shape();
            diff_offset.x_ = -diff_offset.x_ <= max_offset.x_ ? diff_offset.x_ : - max_offset.x_;
            diff_offset.y_ = -diff_offset.y_ <= max_offset.y_ ? diff_offset.y_ : - max_offset.y_;
        }

        global_offset0_ += diff_offset;

        Decorator::set_local_offset(diff_offset);
    }

    void add(Widget *widget) override
    {
        widget_->add(widget);
    }
};