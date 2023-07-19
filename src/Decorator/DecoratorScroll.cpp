#include "DecoratorScroll.hpp"

namespace SL
{
    DecoratorScroll::DecoratorScroll(Widget *widget) : Decorator(widget)
    {}
    
    void DecoratorScroll::scrollEvent (const Event &event)
    {
        if (pointBelong(event.Oleg_.sedata.pos))
        {
            Vector2d offset(0.f, event.Oleg_.sedata.value * 10.f);
            
            Widget *first_child_ = getChildren()[0];
            Widget *last_child_  = getChildren()[0];

            for (auto *child : getChildren())
            {
                first_child_ = first_child_->getPosition().y_ < child->getPosition().y_ ?
                               first_child_ : child;
                last_child_  = last_child_->getPosition().y_  > child->getPosition().y_ ?
                               last_child_ : child;
            }

            auto field = getField();
            auto first_child_field = first_child_->getField();
            auto last_child_field  = last_child_->getField();

            if (field.first.y_ < first_child_field.first.y_ && offset.y_ > 0)
            {
                return;
            }

            if (field.second.y_ > last_child_field.second.y_ && offset.y_ < 0)
            {
                return;
            }

            for (auto *child : getChildren())
            {
                child->setPosition(child->getPosition() + offset);
            }
        }
    }

    void DecoratorScroll::add(Widget *widget)
    {
        widget_->add(widget);
    }
}