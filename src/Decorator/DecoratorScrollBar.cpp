#include "DecoratorScrollBar.hpp"

namespace SL
{
    DecoratorScrollBar::DecoratorScrollBar(Widget *widget) : Decorator(widget),
        scroll_bar_vertical_  (Vector2d(20.f, widget->getShape().y_), Vector2d(widget->getPosition().x_ + widget->getShape().x_ + 10, widget->getPosition().y_), 0.f, 1.f),
        scroll_bar_horizontal_(Vector2d(widget->getShape().x_, 20.f), Vector2d(widget->getPosition().x_, widget->getPosition().y_ + widget->getShape().y_ + 10), 0.f, 1.f),
        current_value_(0, 0)
    {   
        scroll_bar_vertical_.  setScrollCommand ((Command<const Event &> *) new SimpleCommand<DecoratorScrollBar, const Event &> (this, &DecoratorScrollBar::ScrollVerticalWidget));
        scroll_bar_horizontal_.setScrollCommand ((Command<const Event &> *) new SimpleCommand<DecoratorScrollBar, const Event &> (this, &DecoratorScrollBar::ScrollHorizontalWidget));        
    }

    DecoratorScrollBar::~DecoratorScrollBar()
    {
        delete scroll_bar_vertical_.getScrollCommand();
    }

    void DecoratorScrollBar::scrollEvent(const Event &event) 
    {
        if (pointBelong(event.Oleg_.sedata.pos))
        {
            Vector2d offset(0.f, event.Oleg_.sedata.value * 10.f);
            
            float value = scroll_bar_vertical_.getValue() - event.Oleg_.sedata.value * 10.f / getVirtualShape().y_;
            
            if (scroll_bar_vertical_able_)
            {
                scroll_bar_vertical_.setValue(value);
            }
        }
    }
    
    void DecoratorScrollBar::ScrollVerticalWidget(const Event &event)
    {
        sum += current_value_.y_ - event.Oleg_.smedata.value;
        std::cout << getVirtualShape().y_ << "\n";
        float value = (current_value_.y_ - event.Oleg_.smedata.value) * (getVirtualShape().y_ - getShape().y_);
        
        current_value_.y_ = event.Oleg_.smedata.value;
        
        for (auto &child : getChildren())
        {
            child->setPosition(Vector2d(child->getPosition().x_, child->getPosition().y_ + value));
        }
    }

    void DecoratorScrollBar::ScrollHorizontalWidget(const Event &event)
    {
        // float value = (current_value_.x_ - event.Oleg_.smedata.value) * (getVirtualShape().x_ - getShape().x_);
        
        // current_value_.x_ = event.Oleg_.smedata.value;
            
        // for (auto &child : getChildren())
        // {
        //     child->setPosition(Vector2d(child->getPosition().x_ + value, child->getPosition().y_));
        // }
    }

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

        widget_->draw();
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

        widget_->clickLeftEvent(event);
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

        widget_->releaseLeftEvent(event);
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

        widget_->moveMouseEvent(event);
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

        widget_->display(window);
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

        widget_->setParent(parent_widget);
    }
}