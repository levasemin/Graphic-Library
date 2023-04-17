#pragma once

#include "CompositeObject.h"
#include "Button.h"
#include "Container.h"
#include "ComboBox.h"

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
