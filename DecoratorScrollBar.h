#pragma once

#include "Decorator.h"
#include "ScrollBar.h"

class DecoratorScrollBar : public Decorator
{

public:
    DecoratorScrollBar(Widget *widget) : Decorator(widget),
        scroll_bar_(Vector2d(20, widget->get_shape().y_), Vector2d(10, widget->get_shape().y_ / 2), Texture(Colors::Blue))
    {   
        scroll_bar_.set_render_texture(widget->get_render_texture());
        scroll_bar_.set_field();

        scroll_bar_.set_scroll_command ((Command<Vector2d, Vector2d> *) new SimpleCommand<Widget, Vector2d, Vector2d> (this, &Widget::ScrollEvent));
    }

    ScrollBar scroll_bar_;

    void ScrollEvent(Vector2d point, Vector2d offset) override
    {
        double coeff = (scroll_bar_.get_shape().y_ - scroll_bar_.up_button_.get_shape().y_ * 2 - scroll_bar_.scroll_button_.get_shape().y_) /
                       (widget_->get_global_shape().y_ - widget_->get_shape().y_);

        scroll_bar_.scroll_button_.set_offset(offset * -1 * coeff);
        widget_->ScrollEvent(point, offset);
    }


    void draw() override
    {
        if (widget_->get_render_texture() == scroll_bar_.get_render_texture())
        {
            scroll_bar_.draw();
        }

        widget_->draw();
    }
};