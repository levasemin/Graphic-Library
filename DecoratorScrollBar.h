#pragma once

#include "Decorator.h"
#include "RenderTexture.h"
#include "ScrollBar.h"

class DecoratorScrollBar : public Decorator
{
    double coeff_ = 1;
public:
    DecoratorScrollBar(Widget *widget) : Decorator(widget),
        scroll_bar_(Vector2d(20, 500), Vector2d(widget->get_center().x_ - widget->get_shape().x_ / 2 - 10, widget_->get_center().y_))
    {   
        scroll_bar_.set_scroll_command ((Command<const Event &> *) new SimpleCommand<DecoratorScrollBar, const Event &> (this, &DecoratorScrollBar::ScrollWidget));
    }

    ScrollBar scroll_bar_;

    void ScrollEvent(const Event &event) override
    {
        if (point_belonging(Vector2d(event.Oleg_.sedata.x, event.Oleg_.sedata.y)))
        {   
            Event new_event = event;
            new_event.Oleg_.sedata.value = event.Oleg_.sedata.value / (widget_->get_global_shape().y_ - widget_->get_shape().y_);
            scroll_bar_.scroll_bar(new_event);
        }
    }

    void ScrollWidget(const Event &event)
    {
        widget_->set_local_offset(Vector2d(0, event.Oleg_.smedata.value * (widget_->get_global_shape().y_ - widget_->get_shape().y_)));
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

    void set_global_offset(Vector2d diff_offset) override
    {
        scroll_bar_.set_global_offset(diff_offset);
        widget_->set_global_offset(diff_offset);
    }

    bool point_belonging(Vector2d point) const override
    {
        return widget_->point_belonging(point) || scroll_bar_.point_belonging(point);
    }

    void display(Window *window) override
    {
        scroll_bar_.display(window);
        widget_->display(window);
    }

    void set_parent(Widget *parent_widget) override
    {
        widget_->set_parent(parent_widget);
        scroll_bar_.set_parent(parent_widget);
    }
};