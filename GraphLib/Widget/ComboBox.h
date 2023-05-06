#pragma once

#include "../Classes/Texture.h"
#include "../Widget/CompositeObject.h"
#include "../Event/Command.h"
#include "../Widget/Button.h"
#include "../Event/SimpleCommand.h"
#include "../Widget/Container.h"

namespace SL
{
    class ComboBox : public Button
    {
        bool is_showed_ = false;
        Container item_box_;

    public:

        ComboBox(Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::Blue)) : Button(shape, position, texture),
            item_box_(Vector2d(shape.x_ * 2, shape.y_ * 10), position + Vector2d(0.f, shape.y_))
        {
        }

        void ClickLeftEvent(const Event &event) override
        {
            if (point_belonging(event.Oleg_.mbedata.pos))
            {
                if (is_showed_)
                {
                    parent_->remove(&item_box_);
                }

                else
                {
                    parent_->add(&item_box_);
                }

                is_showed_ = !is_showed_;
            }

            else if (is_showed_)
            {
                if (!item_box_.point_belonging(event.Oleg_.mbedata.pos) && !point_belonging(event.Oleg_.mbedata.pos))
                {
                    parent_->remove(&item_box_);
                    is_showed_ = false;
                }
            }
        }

        void add(Widget *widget) override
        {
            item_box_.add(widget);
        }
        
        Vector2d get_box_shape()
        {
            return item_box_.get_shape();
        }

        void set_box_shape(const Vector2d &shape)
        {
            item_box_.set_shape(shape);
        }
        
        void set_box_texture(const Texture &texture)
        {
            item_box_.set_texture(texture);
        }
    };
}