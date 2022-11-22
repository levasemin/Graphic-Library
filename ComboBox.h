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
public:
    Container item_box_;

    ComboBox(Vector2d shape, Vector2d center, const Texture &texture = Texture(Colors::Blue), Widget *parent = nullptr) : Button(shape, center, texture, parent),
        item_box_(Vector2d(100, 200), center + Vector2d(0, shape.y_ / 2 + 100), Texture(Colors::White), parent)

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
};