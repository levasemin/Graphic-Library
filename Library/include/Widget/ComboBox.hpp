#pragma once

#include "Texture.hpp"
#include "CompositeObject.hpp"
#include "Command.hpp"
#include "Button.hpp"
#include "SimpleCommand.hpp"
#include "Container.hpp"

namespace SL
{
    class ComboBox : public Button
    {
    public:

        ComboBox(Vector2d shape, Vector2d position, const Texture &texture);

        void ClickLeftEvent(const Event &event) override;

        void add(Widget *widget) override;
        
        Vector2d get_box_shape();

        void set_box_shape(const Vector2d &shape);
        
        void set_box_texture(const Texture &texture);
    
    private:
        bool is_showed_ = false;
        Container item_box_;
    };
}