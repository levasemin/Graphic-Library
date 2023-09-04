#include "DecoratorScroll.hpp"

namespace SL
{    
    DecoratorScroll::DecoratorScroll (Widget *widget, Vector2d shape, Vector2d position, const Texture &texture):
        CompositeObject(shape, position, texture),
        widget_(widget),
        offset_(0)
    {
        setWidget(widget);
    }

    DecoratorScroll::DecoratorScroll(const DecoratorScroll &source): CompositeObject(source),
        widget_(source.widget_),
        offset_(source.offset_)
    {
        *widget_ = *source.widget_;
        scroll_shape_ = widget_->getShape().y_ + widget_->getPosition().y_;
    }
    
    DecoratorScroll &DecoratorScroll::operator=(const DecoratorScroll &source)
    {
        CompositeObject::operator=(source);
        *widget_  = *source.widget_;
        offset_   = source.offset_;
        scroll_shape_ = widget_->getShape().y_ + widget_->getPosition().y_;
        return *this;
    }

    DecoratorScroll::DecoratorScroll(DecoratorScroll &&source): CompositeObject(source),
        widget_(source.widget_),
        offset_(source.offset_)
    {
        CompositeObject::add(widget_);
        scroll_shape_ = widget_->getShape().y_ + widget_->getPosition().y_;
    }

    DecoratorScroll &DecoratorScroll::operator=(DecoratorScroll &&source)
    {
        CompositeObject::operator=(source);
        CompositeObject::remove(widget_);
        widget_ = source.widget_;
        CompositeObject::add(widget_);
        offset_ = source.offset_;
        scroll_shape_ = widget_->getShape().y_ + widget_->getPosition().y_;
        return *this;
    }


    Widget *DecoratorScroll::getWidget()
    {
        return widget_;
    }

    void DecoratorScroll::setWidget(Widget *widget)
    {
        CompositeObject::remove(widget_);
        widget_ = widget;
        CompositeObject::add(widget_);
        offset_ = 0;
        scroll_shape_ = widget_->getShape().y_ + widget_->getPosition().y_;
    }
    
    void DecoratorScroll::add(Widget *window)
    {
        widget_->add(window);
    }

    void DecoratorScroll::remove(Widget *window)
    {
        widget_->remove(window);
    }

    
//protected
    void DecoratorScroll::scrollEvent (const Event &event)
    {
        if (pointBelong(event.Oleg_.msedata.pos))
        {
            float offset = event.Oleg_.msedata.value * 10.f;

            if (offset_ + offset > 0)
            {
                return;
            }
            
            if (offset_ + offset < getShape().y_ - scroll_shape_)
            {
                return;
            }

            offset_ += offset;
            
            widget_->setPosition(widget_->getPosition() + Vector2d(0.f, offset));

            CompositeObject::scrollEvent(event);
        }
    }
}