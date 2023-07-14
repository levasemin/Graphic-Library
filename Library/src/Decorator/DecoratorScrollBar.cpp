#include "DecoratorScrollBar.hpp"

namespace SL
{
    DecoratorScrollBar::DecoratorScrollBar(Widget *widget) : Decorator(widget),
        scroll_bar_vertical_  (Vector2d(20.f, widget->get_shape().y_), Vector2d(widget->get_position().x_ + widget->get_shape().x_ + 10, widget->get_position().y_), 0.f, 1.f),
        scroll_bar_horizontal_(Vector2d(widget->get_shape().x_, 20.f), Vector2d(widget->get_position().x_, widget->get_position().y_ + widget->get_shape().y_ + 10), 0.f, 1.f)
    {   
        scroll_bar_vertical_.set_scroll_command   ((Command<const Event &> *) new SimpleCommand<DecoratorScrollBar, const Event &> (this, &DecoratorScrollBar::ScrollVerticalWidget));
        scroll_bar_horizontal_.set_scroll_command ((Command<const Event &> *) new SimpleCommand<DecoratorScrollBar, const Event &> (this, &DecoratorScrollBar::ScrollHorizontalWidget));        
    }


    void DecoratorScrollBar::ScrollEvent(const Event &event) 
    {
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.ScrollEvent(event);
        }

        if (point_belonging(event.Oleg_.sedata.pos))
        {               
            if (doublecmp(widget_->get_global_shape().y_, widget_->get_shape().y_))
            {
                float value = (float)( event.Oleg_.sedata.value * 2 / (widget_->get_global_shape().y_ - widget_->get_shape().y_) +
                                            widget_->get_local_offset().y_ / (widget_->get_global_shape().y_ - widget_->get_shape().y_));
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
        Vector2d offset = get_local_offset();
        offset.y_ = - event.Oleg_.smedata.value * (widget_->get_global_shape().y_ - widget_->get_shape().y_);
        widget_->set_local_offset(offset);
    }

    void DecoratorScrollBar::ScrollHorizontalWidget(const Event &event)
    {
        Vector2d offset = get_local_offset();
        offset.x_ = - event.Oleg_.smedata.value * (widget_->get_global_shape().x_ - widget_->get_shape().x_);
        widget_->set_local_offset(offset);
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

    void DecoratorScrollBar::ClickLeftEvent (const Event &event) 
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.ClickLeftEvent(event);
        }
        
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.ClickLeftEvent(event);
        }

        widget_->ClickLeftEvent(event);
    }

    void DecoratorScrollBar::ReleasedLeftEvent (const Event &event) 
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.ReleasedLeftEvent(event);
        }
        
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.ReleasedLeftEvent(event);
        }

        widget_->ReleasedLeftEvent(event);
    }            
    
    void DecoratorScrollBar::MoveMouseEvent (const Event &event) 
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.MoveMouseEvent(event);
        }
        
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.MoveMouseEvent(event);
        }

        widget_->MoveMouseEvent(event);
    }

    void DecoratorScrollBar::set_global_offset(Vector2d offset) 
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.set_global_offset(offset);
        }
        
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.set_global_offset(offset);
        }

        widget_->set_global_offset(offset);
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

    void DecoratorScrollBar::set_parent(Widget *parent_widget) 
    {
        if (scroll_bar_horizontal_able_)
        {
            scroll_bar_horizontal_.set_parent(parent_widget);
        }
        
        if (scroll_bar_vertical_able_)
        {
            scroll_bar_vertical_.set_parent(parent_widget);
        }

        widget_->set_parent(parent_widget);
    }
}