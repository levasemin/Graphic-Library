#pragma once

#include "Decorator.h"
#include "RenderTexture.h"
#include "ScrollBar.h"

class DecoratorScrollBar : public Decorator
{

public:
    DecoratorScrollBar(Widget *widget) : Decorator(widget),
        scroll_bar_(Vector2d(20, 500), Vector2d(widget->get_center().x_ - widget->get_shape().x_ / 2 - 10, widget_->get_center().y_), Texture(Colors::Blue))
    {   
        scroll_bar_.set_scroll_command ((Command<const Event &> *) new SimpleCommand<DecoratorScrollBar, const Event &> (this, &DecoratorScrollBar::ScrollWidget));
    }

    ScrollBar scroll_bar_;

    void ScrollEvent(const Event &event) override
    {
        if (point_belonging(Vector2d(event.Oleg_.smedata.x, event.Oleg_.smedata.y)))
        {   
            double coeff = (scroll_bar_.get_shape().y_ - scroll_bar_.up_button_.get_shape().y_ * 2 - scroll_bar_.scroll_button_.get_shape().y_) /
                           (widget_->get_global_shape().y_ - widget_->get_shape().y_);

            Event new_event = event;
            new_event.Oleg_.smedata.value *= coeff;
            scroll_bar_.ScrollEvent(new_event);
        }
    }


    void ScrollWidget(const Event &event)
    {
        double coeff = (scroll_bar_.get_shape().y_ - scroll_bar_.up_button_.get_shape().y_ * 2 - scroll_bar_.scroll_button_.get_shape().y_) /
                       (widget_->get_global_shape().y_ - widget_->get_shape().y_);
        
        Event new_event = event;
        new_event.Oleg_.smedata.value *= 1 / coeff;
        widget_->ScrollEvent(new_event);
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
    
    void PressLeftEvent (const Event &event) override
    {
        scroll_bar_.PressLeftEvent(event);
        widget_->PressLeftEvent(event);
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

    void PressRightEvent (const Event &event) override
    {
        scroll_bar_.PressRightEvent(event);
        widget_->PressRightEvent(event);
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