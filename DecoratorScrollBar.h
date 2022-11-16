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
        scroll_bar_.set_scroll_command ((Command<Vector2d, Vector2d> *) new SimpleCommand<DecoratorScrollBar, Vector2d, Vector2d> (this, &DecoratorScrollBar::ScrollWidget));
    }

    ScrollBar scroll_bar_;

    void ScrollEvent(Vector2d point, Vector2d offset) override
    {
        if (point_belonging(point))
        {   
            double coeff = (scroll_bar_.get_shape().y_ - scroll_bar_.up_button_.get_shape().y_ * 2 - scroll_bar_.scroll_button_.get_shape().y_) /
                           (widget_->get_global_shape().y_ - widget_->get_shape().y_);

            scroll_bar_.ScrollEvent(point, offset * coeff);
        }
    }


    void ScrollWidget(Vector2d point, Vector2d offset)
    {
        double coeff = (scroll_bar_.get_shape().y_ - scroll_bar_.up_button_.get_shape().y_ * 2 - scroll_bar_.scroll_button_.get_shape().y_) /
                           (widget_->get_global_shape().y_ - widget_->get_shape().y_);
        
        widget_->ScrollEvent(point, offset * (1 / coeff));
    }

    void draw() override
    {
        scroll_bar_.draw();

        widget_->draw();
    }

    void ClickLeftEvent (Vector2d point) override
    {
        scroll_bar_.ClickLeftEvent(point);
        widget_->ClickLeftEvent(point);
    }
    
    void PressLeftEvent (Vector2d point) override
    {
        scroll_bar_.PressLeftEvent(point);
        widget_->PressLeftEvent(point);
    }
    
    void ReleasedLeftEvent (Vector2d point) override
    {
        scroll_bar_.ReleasedLeftEvent(point);
        widget_->ReleasedLeftEvent(point);
    }              

    virtual void ClickRightEvent (Vector2d point) override
    {
        scroll_bar_.ClickRightEvent(point);
        widget_->ClickRightEvent(point);
    }

    void PressRightEvent (Vector2d point) override
    {
        scroll_bar_.PressRightEvent(point);
        widget_->PressRightEvent(point);
    }               
    
    void ReleasedRightEvent (Vector2d point) override
    {
        scroll_bar_.ReleasedRightEvent(point);
        widget_->ReleasedRightEvent(point);
    }              
    
    void MoveMouseEvent (Vector2d point) override
    {
        scroll_bar_.MoveMouseEvent(point);
        widget_->MoveMouseEvent(point);
    }

    void PressKeyEvent (int key) override
    {
        scroll_bar_.MoveMouseEvent(key);
        widget_->PressKeyEvent(key);
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