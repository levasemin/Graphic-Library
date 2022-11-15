#include "Decorator.h"

class DecoratorScroll : public Decorator
{
    Vector2d global_offset0_ = (0, 0);

public :
    DecoratorScroll(Widget *widget) : Decorator(widget)
    {
    }

    void ScrollEvent (Vector2d point, Vector2d offset) override
    {
        if (offset.y_ > 0)
        {
            offset.x_ = offset.x_ <= -global_offset0_.x_ ? offset.x_ :  -global_offset0_.x_;
            offset.y_ = offset.y_ <= -global_offset0_.y_ ? offset.y_ :  -global_offset0_.y_;
        }
        
        if (offset.y_ < 0)
        {
            Vector2d max_offset =  global_offset0_ + widget_->get_global_shape() - widget_->get_shape();
            offset.x_ = -offset.x_ <= max_offset.x_ ? offset.x_ : - max_offset.x_;
            offset.y_ = -offset.y_ <= max_offset.y_ ? offset.y_ : - max_offset.y_;
        }

        global_offset0_ += offset;

        set_local_offset(offset);
    }
};