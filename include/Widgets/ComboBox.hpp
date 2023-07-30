#pragma once

#include "Texture.hpp"
#include "CompositeObject.hpp"
#include "Event.hpp"
#include "Button.hpp"
#include "Container.hpp"

namespace SL
{
    class ComboBox : public Button
    {
    public:
        ComboBox(Vector2d shape, Vector2d position, const Texture &texture);

        ComboBox(const ComboBox &source) = default;
        ComboBox &operator=(const ComboBox &source) = default;
        ~ComboBox() = default;

        Vector2d get_box_shape();

        void set_box_shape(const Vector2d &shape);

        void add(Widget *widget) override;

        void set_box_texture(const Texture &texture);
    
    protected:
        void clickLeftEvent(const Event &event) override;    
    
    private:
        bool is_showed_ = false;
        Container item_box_;
    };
}