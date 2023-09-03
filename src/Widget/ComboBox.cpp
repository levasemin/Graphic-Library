#include "ComboBox.hpp"

namespace SL
{

    ComboBox::ComboBox(Vector2d shape, Vector2d position, const Texture &texture) : Button(shape, position, texture),
                item_box_(Vector2d(shape.x_ * 2, shape.y_ * 10), position + Vector2d(0.f, shape.y_))
    {
    }

    void ComboBox::clickEvent(const Event &event)
    {
        if (pointBelong(event.Oleg_.mpedata.pos))
        {
            if (is_showed_)
            {
                getParent()->remove(&item_box_);
            }

            else
            {
                getParent()->add(&item_box_);
            }

            is_showed_ = !is_showed_;
        }

        else if (is_showed_)
        {
            // if (!item_box_.pointBelong(event.Oleg_.mpedata.pos) && !pointBelong(event.Oleg_.mpedata.pos))
            // {
            //     getParent()->remove(&item_box_);
            //     is_showed_ = false;
            // }
        }
    }

    void ComboBox::add(Widget *widget) 
    {
        item_box_.add(widget);
    }

    Vector2d ComboBox::get_box_shape()
    {
        return item_box_.getShape();
    }

    void ComboBox::set_box_shape(const Vector2d &shape)
    {
        item_box_.setShape(shape);
    }

    void ComboBox::set_box_texture(const Texture &texture)
    {
        item_box_.setTexture(texture);
    }
}