#pragma once

#include "CompositeObject.hpp"
#include "Button.hpp"
#include "Container.hpp"
#include "ComboBox.hpp"

namespace SL
{
    class MenuBar : public CompositeObject
    {
    public:

        MenuBar(Vector2d shape, Vector2d position, Texture texture = Texture(Color::White)) : 
            CompositeObject(shape, position, texture)
            {

            }

        void add(Widget *) override
        {
            
        }
    };
}