#pragma once

#include "Decorator.h"
#include "RenderTexture.h"
#include "ScrollBar.h"

class DecoratorScrollBar : public Decorator
{
public:
    DecoratorScrollBar(Widget *widget) : Decorator(widget),
        scroll_bar_(Vector2d(20, widget->get_shape().y_), Vector2d(widget->get_center().x_ + widget->get_shape().x_ / 2 + 10, widget->get_center().y_))
    {   
        scroll_bar_.set_scroll_command ((Command<const Event &> *) new SimpleCommand<DecoratorScrollBar, const Event &> (this, &DecoratorScrollBar::ScrollWidget));
    }

    ScrollBar scroll_bar_;

    void ScrollEvent(const Event &event) override
    {
        scroll_bar_.ScrollEvent(event);

        if (point_belonging(Vector2d(event.Oleg_.sedata.x, event.Oleg_.sedata.y)))
        {   
            Event new_event = event;
            new_event.Oleg_.smedata.value = event.Oleg_.sedata.value / (widget_->get_global_shape().y_ - widget_->get_shape().y_) +
                                           widget_->get_local_offset().y_ / (widget_->get_global_shape().y_ - widget_->get_shape().y_);
            new_event.Oleg_.smedata.value *= -1;
            scroll_bar_.scroll_bar(new_event);
        }
    }

    void ScrollWidget(const Event &event)
    {
        Vector2d offset(0, 0);
        offset.y_ = - event.Oleg_.smedata.value * (widget_->get_global_shape().y_ - widget_->get_shape().y_);
        widget_->set_local_offset(offset);
    }

    void draw() override
    {
        scroll_bar_.draw();
        widget_->draw();
    }

    void ClickLeftEvent (const Event &event) override
    {
        scroll_bar_.ClickLeftEvent(event);
        widget_->ClickLeftEvent(event);
    }

    void ReleasedLeftEvent (const Event &event) override
    {
        scroll_bar_.ReleasedLeftEvent(event);
        widget_->ReleasedLeftEvent(event);
    }              

    virtual void ClickRightEvent (const Event &event) override
    {
        scroll_bar_.ClickRightEvent(event);
        widget_->ClickRightEvent(event);
    }           
    
    void ReleasedRightEvent (const Event &event) override
    {   
        scroll_bar_.ReleasedRightEvent(event);
        widget_->ReleasedRightEvent(event);
    }              
    
    void MoveMouseEvent (const Event &event) override
    {
        scroll_bar_.MoveMouseEvent(event);
        widget_->MoveMouseEvent(event);
    }

    void PressKeyEvent (const Event &event) override
    {
        scroll_bar_.MoveMouseEvent(event);
        widget_->PressKeyEvent(event);
    }

    void set_global_offset(Vector2d offset) override
    {
        scroll_bar_.set_global_offset(offset);
        widget_->set_global_offset(offset);
    }

    void display(Window *window) override
    {
        scroll_bar_.display(window);
        widget_->display(window);
    }

    void set_parent(Widget *parent_widget) override
    {
        scroll_bar_.set_parent(parent_widget);
        widget_->set_parent(parent_widget);
    }
};