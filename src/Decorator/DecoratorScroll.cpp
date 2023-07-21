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

    DecoratorScroll::~DecoratorScroll()
    {
        delete widget_;
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

    Vector2d DecoratorScroll::getDecoratorShape() const
    {
        return CompositeObject::getShape();
    }

    void DecoratorScroll::setDecoratorShape (Vector2d shape)
    {
        CompositeObject::setShape(shape);
    }

    Vector2d DecoratorScroll::getDecoratorPosition() const
    {
        return CompositeObject::getPosition();
    }

    void DecoratorScroll::setDecoratorPosition(Vector2d position)
    {
        CompositeObject::setPosition(position);
    }

    void DecoratorScroll::add(Widget *window)
    {
        widget_->add(window);
    }

    void DecoratorScroll::remove(Widget *window)
    {
        widget_->remove(window);
    }
    
    Vector2d DecoratorScroll::getPosition() const
    {
        return widget_->getPosition();
    }

    void DecoratorScroll::setPosition(Vector2d position)
    {
        widget_->setPosition(position);
    }

    Vector2d DecoratorScroll::getShape() const
    {
        return widget_->getShape();
    }

    void DecoratorScroll::setShape (Vector2d shape)
    {
        widget_->setShape(shape);
    }

    Texture DecoratorScroll::getTexture () const
    {
        return widget_->getTexture();
    }

    void DecoratorScroll::setTexture (const Texture &texture)
    {
        widget_->setTexture(texture);
    }
    
//protected
    void DecoratorScroll::scrollEvent (const Event &event)
    {
        if (pointBelong(event.Oleg_.sedata.pos))
        {
            float offset = event.Oleg_.sedata.value * 10.f;

            if (offset_ + offset > 0)
            {
                return;
            }
            
            if (offset_ + offset < shape_.y_ - scroll_shape_)
            {
                return;
            }

            offset_ += offset;
            
            widget_->setPosition(widget_->getPosition() + Vector2d(0.f, offset));

            CompositeObject::scrollEvent(event);
        }
    }
}