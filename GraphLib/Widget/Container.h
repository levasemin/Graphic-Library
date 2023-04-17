#pragma once

#include "../Classes/Texture.h"
#include "../Application/Window.h"
#include "../Widget/Widget.h"
#include "../Classes/Vector2d.h"

class Container : public CompositeObject
{
public:

    Container(Vector2d shape, Vector2d position): 
        CompositeObject(shape, position)
        {}
};