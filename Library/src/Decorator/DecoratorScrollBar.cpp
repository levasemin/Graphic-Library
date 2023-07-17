#include "DecoratorScrollBar.hpp"

namespace SL
{
    DecoratorScrollBar::DecoratorScrollBar(Widget *widget) : Decorator(widget),
        scroll_bar_vertical_  (Vector2d(20.f, widget->getShape().y_), Vector2d(widget->getPosition().x_ + widget->getShape().x_ + 10, widget->getPosition().y_), 0.f, 1.f),
        scroll_bar_horizontal_(Vector2d(widget->getShape().x_, 20.f), Vector2d(widget->getPosition().x_, widget->getPosition().y_ + widget->getShape().y_ + 10), 0.f, 1.f)
    {   
        scroll_bar_vertical_.set_scroll_command   ((Command<const Event &> *) new SimpleCommand<DecoratorScrollBar, const Event &> (this, &DecoratorScrollBar::ScrollVerticalWidget));
        scroll_bar_horizontal_.set_scroll_command ((Command<const Event &> *) new SimpleCommand<DecoratorScrollBar, const Event &> (this, &DecoratorScrollBar::ScrollHorizontalWidget));        
    }


    void DecoratorScrollBar::scrollEvent(const Event &event) 
    {
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.scrollEvent(event);
        }

        if (pointBelong(event.Oleg_.sedata.pos))
        {               
            if (doublecmp(widget_->getGlobalShape().y_, widget_->getShape().y_))
            {
                float value = (float)( event.Oleg_.sedata.value * 2 / (widget_->getGlobalShape().y_ - widget_->getShape().y_) +
                                            widget_->getLocalOffset().y_ / (widget_->getGlobalShape().y_ - widget_->getShape().y_));
                value *= -1;
                
                if (scroll_bar_vertical_able_)
                {
                    scroll_bar_vertical_.scroll_bar(value);
                }
            }
        }
    }

    void DecoratorScrollBar::ScrollVerticalWidget(const Event &event)
    {
        Vector2d offset = getLocalOffset();
        offset.y_ = - event.Oleg_.smedata.value * (widget_->getGlobalShape().y_ - widget_->getShape().y_);
        widget_->setLocalOffset(offset);
    }

    void DecoratorScrollBar::ScrollHorizontalWidget(const Event &event)
    {
        Vector2d offset = getLocalOffset();
        offset.x_ = - event.Oleg_.smedata.value * (widget_->getGlobalShape().x_ - widget_->getShape().x_);
        widget_->setLocalOffset(offset);
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

    void DecoratorScrollBar::setGlobalOffset(Vector2d offset) 
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.setGlobalOffset(offset);
        }
        
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.setGlobalOffset(offset);
        }

        widget_->setGlobalOffset(offset);
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