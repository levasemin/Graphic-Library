#include "Texture.h"
#include "CompositeObject.h"
#include "Command.h"
#include "Button.h"
#include "SimpleCommand.h"
#include "Command.h"
#include "Container.h"

class ComboBox : public Button
{
    bool is_showed_ = false;
    Container item_box_;

public:

    ComboBox(Vector2d shape, Vector2d center, const Texture &texture = Texture(Colors::Blue), Widget *parent = nullptr) : Button(shape, center, texture, parent),
        item_box_(Vector2d(1, 1), center + Vector2d(0, shape.y_ / 2), Texture(Colors::White), parent)
    {
        if (parent_ != nullptr)
        {
            parent_->add(&item_box_);
        }

        set_left_click((Command<const Event&> *)new SimpleCommand<ComboBox, const Event &>(this, &ComboBox::show_item_container));
    }

    void show_item_container(const Event &)
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
        item_box_.set_center(center_ + shape_.y_ / 2 + item_box_.get_shape().y_ / 2);
    }
};