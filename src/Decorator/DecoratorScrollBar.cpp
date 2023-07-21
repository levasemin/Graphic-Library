#include "DecoratorScrollBar.hpp"

namespace SL
{
    DecoratorScrollBar::DecoratorScrollBar(Widget *widget, Vector2d shape, Vector2d position, const Texture &texture): 
        CompositeObject(shape, position, texture),
        widget_(widget),
        scroll_bar_vertical_  (Vector2d(20.f, shape.y_), Vector2d(position.x_ + shape.x_ + 10, position.y_), 0.f, 1.f),
        scroll_bar_horizontal_(Vector2d(shape.x_, 20.f), Vector2d(position.x_, position.y_ + shape.y_ + 10), 0.f, 1.f),
        current_value_(0, 0),
        scroll_shape_(widget_->getPosition().x_ + widget_->getShape().x_, widget_->getPosition().y_ + widget_->getShape().y_)
    {   
        CompositeObject::add(widget);
        
        scroll_bar_vertical_.  setScrollCommand ((Command<const Event &> *) new SimpleCommand<DecoratorScrollBar, const Event &> (this, &DecoratorScrollBar::ScrollVerticalWidget));
        scroll_bar_horizontal_.setScrollCommand ((Command<const Event &> *) new SimpleCommand<DecoratorScrollBar, const Event &> (this, &DecoratorScrollBar::ScrollHorizontalWidget));        
    }

    DecoratorScrollBar::~DecoratorScrollBar()
    {
        delete scroll_bar_vertical_.getScrollCommand();
        delete scroll_bar_horizontal_.getScrollCommand();
    }

    void DecoratorScrollBar::add(Widget *child)
    {
        widget_->add(child);
    }

    void DecoratorScrollBar::remove(Widget *child)
    {
        widget_->remove(child);
    }
    
    Vector2d DecoratorScrollBar::getPosition() const
    {
        return widget_->getPosition();
    }

    void DecoratorScrollBar::setPosition(Vector2d position)
    {
        widget_->setPosition(position);
    }

    Vector2d DecoratorScrollBar::getShape () const 
    {
        return widget_->getShape();
    }

    void DecoratorScrollBar::setShape (Vector2d shape)
    {
        widget_->setShape(shape);
    }

    Texture DecoratorScrollBar::getTexture () const
    {
        return widget_->getTexture();
    }

    void DecoratorScrollBar::setTexture (const Texture &texture)
    {
        widget_->setTexture(texture);
    }

    Vector2d DecoratorScrollBar::getDecoratorShape() const
    {
        return shape_;
    }

    void DecoratorScrollBar::setDecoratorShape (Vector2d shape)
    {
        shape_ = shape;
    }

    Vector2d DecoratorScrollBar::getDecoratorPosition() const
    {
        return position_;
    }

    void DecoratorScrollBar::setDecoratorPosition(Vector2d position)
    {
        position_ = position;
    }
        
    Widget *DecoratorScrollBar::getWidget()
    {
        return widget_;
    }

    void DecoratorScrollBar::setWidget(Widget *widget)
    {
        widget_ = widget;
    }

//protected
    void DecoratorScrollBar::draw() 
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.draw();
        }

        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.draw();
        }

        CompositeObject::draw();
    }

    void DecoratorScrollBar::display(Window *window) 
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.display(window);
        }
        
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.display(window);
        }

        CompositeObject::display(window);
    }

    void DecoratorScrollBar::setParent(Widget *parent_widget) 
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.setParent(parent_widget);
        }
        
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.setParent(parent_widget);
        }

        CompositeObject::setParent(parent_widget);
    }

    void DecoratorScrollBar::scrollEvent(const Event &event) 
    {
        if (pointBelong(event.Oleg_.sedata.pos))
        {
            Vector2d offset(0.f, event.Oleg_.sedata.value * 10.f);
            
            float value = scroll_bar_vertical_.getValue() - event.Oleg_.sedata.value * 10.f / scroll_shape_.y_;
            
            if (scroll_bar_vertical_able_)
            {
                scroll_bar_vertical_.setValue(value);
            }
        }

        CompositeObject::scrollEvent(event);
    }

    void DecoratorScrollBar::clickLeftEvent (const Event &event) 
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.clickLeftEvent(event);
        }
        
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.clickLeftEvent(event);
        }

        CompositeObject::clickLeftEvent(event);
    }

    void DecoratorScrollBar::releaseLeftEvent (const Event &event) 
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.releaseLeftEvent(event);
        }
        
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.releaseLeftEvent(event);
        }

        CompositeObject::releaseLeftEvent(event);
    }            
    
    void DecoratorScrollBar::moveMouseEvent (const Event &event) 
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.moveMouseEvent(event);
        }
        
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.moveMouseEvent(event);
        }

        CompositeObject::moveMouseEvent(event);
    }
    
//private
    void DecoratorScrollBar::ScrollVerticalWidget(const Event &event)
    {
        float value = (current_value_.y_ - event.Oleg_.smedata.value) * (scroll_shape_.y_ - getShape().y_);
        
        current_value_.y_ = event.Oleg_.smedata.value;
        
        widget_->setPosition(Vector2d(widget_->getPosition().x_, widget_->getPosition().y_ + value));
    }

    void DecoratorScrollBar::ScrollHorizontalWidget(const Event &event)
    {
        float value = (current_value_.x_ - event.Oleg_.smedata.value) * (scroll_shape_.x_ - getShape().x_);
        
        current_value_.x_ = event.Oleg_.smedata.value;
            
        widget_->setPosition(Vector2d(widget_->getPosition().x_ + value, widget_->getPosition().y_));
    }
}