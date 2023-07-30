#include "DecoratorScrollBar.hpp"

namespace SL
{
    DecoratorScrollBar::DecoratorScrollBar(Widget *widget, Vector2d shape, Vector2d position, const Texture &texture): 
        CompositeObject(shape, position, texture),
        widget_(widget),
        scroll_bar_vertical_  (Vector2d(20.f, shape.y_ - 20.f), Vector2d(shape.x_ - 20.f, 0.f), 0.f, 1.f),
        scroll_bar_horizontal_(Vector2d(shape.x_ - 20.f, 20.f), Vector2d(0.f, shape.y_ - 20.f), 0.f, 1.f),
        scroll_container_(shape - 20.f, Vector2d(0, 0)),
        current_value_(0, 0),
        scroll_shape_(widget_->getPosition().x_ + widget_->getShape().x_, widget_->getPosition().y_ + widget_->getShape().y_)
    {   
        scroll_container_.add(widget);
        
        CompositeObject::add(&scroll_container_);
        CompositeObject::add(&scroll_bar_horizontal_);
        CompositeObject::add(&scroll_bar_vertical_);

        
        scroll_bar_vertical_.  setScrollCommand ((Command<float> *) new SimpleCommand<DecoratorScrollBar, float> (this, &DecoratorScrollBar::ScrollVerticalWidget));
        scroll_bar_horizontal_.setScrollCommand ((Command<float> *) new SimpleCommand<DecoratorScrollBar, float> (this, &DecoratorScrollBar::ScrollHorizontalWidget));        
    }

    DecoratorScrollBar::DecoratorScrollBar(const DecoratorScrollBar &source) : CompositeObject(*(CompositeObject *)&source),
        widget_(source.widget_),
        scroll_bar_horizontal_able_(source.scroll_bar_horizontal_able_),
        scroll_bar_vertical_able_(source.scroll_bar_vertical_able_),
        scroll_container_(source.scroll_container_),
        current_value_(source.current_value_),
        scroll_shape_(source.scroll_shape_),
//TODO
        scroll_bar_vertical_(source.scroll_bar_vertical_),
        scroll_bar_horizontal_(source.scroll_bar_horizontal_)
    {
        scroll_bar_vertical_.  setScrollCommand ((Command<float> *) new SimpleCommand<DecoratorScrollBar, float> (this, &DecoratorScrollBar::ScrollVerticalWidget));
        scroll_bar_horizontal_.setScrollCommand ((Command<float> *) new SimpleCommand<DecoratorScrollBar, float> (this, &DecoratorScrollBar::ScrollHorizontalWidget)); 
    }

    DecoratorScrollBar &DecoratorScrollBar::operator=(const DecoratorScrollBar &source)
    {
        CompositeObject::operator=(*(CompositeObject *)&source);
        
        widget_ = source.widget_;
        scroll_bar_horizontal_able_ = source.scroll_bar_horizontal_able_;
        scroll_bar_vertical_able_ = source.scroll_bar_vertical_able_;
        scroll_container_ = source.scroll_container_;
        current_value_ = source.current_value_;
        scroll_shape_ = source.scroll_shape_;
//TODO
        // scroll_bar_vertical_ = source.scroll_bar_vertical_;
        // scroll_bar_horizontal_ = source.scroll_bar_horizontal_;

        scroll_bar_vertical_.  setScrollCommand ((Command<float> *) new SimpleCommand<DecoratorScrollBar, float> (this, &DecoratorScrollBar::ScrollVerticalWidget));
        scroll_bar_horizontal_.setScrollCommand ((Command<float> *) new SimpleCommand<DecoratorScrollBar, float> (this, &DecoratorScrollBar::ScrollHorizontalWidget)); 

        return *this;
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
        
    Widget *DecoratorScrollBar::getWidget()
    {
        return widget_;
    }

    void DecoratorScrollBar::setWidget(Widget *widget)
    {
        scroll_container_.remove(widget_);
        widget_ = widget;
        scroll_container_.add(widget_);
        current_value_ = Vector2d(0, 0);
        scroll_shape_ = widget_->getShape().y_ + widget_->getPosition().y_;
    }

//protected

    void DecoratorScrollBar::scrollEvent(const Event &event) 
    {
        if (pointBelong(event.Oleg_.mwsedata.pos))
        {
            Vector2d offset(0.f, event.Oleg_.mwsedata.value * 10.f);
            
            float value = scroll_bar_vertical_.getValue() - event.Oleg_.mwsedata.value * 10.f / scroll_shape_.y_;
            
            if (scroll_bar_vertical_able_)
            {
                scroll_bar_vertical_.setValue(value);
            }
        }

        CompositeObject::scrollEvent(event);
    } 
    

    
//private
    void DecoratorScrollBar::ScrollVerticalWidget(float value_)
    {
        float value = (current_value_.y_ - value_) * (scroll_shape_.y_ - scroll_container_.getShape().y_);
        
        current_value_.y_ = value_;
        
        widget_->setPosition(Vector2d(widget_->getPosition().x_, widget_->getPosition().y_ + value));
    }

    void DecoratorScrollBar::ScrollHorizontalWidget(float value_)
    {
        float value = (current_value_.x_ - value_) * (scroll_shape_.x_ - scroll_container_.getShape().x_);
        
        current_value_.x_ = value_;
            
        widget_->setPosition(Vector2d(widget_->getPosition().x_ + value, widget_->getPosition().y_));
    }
}