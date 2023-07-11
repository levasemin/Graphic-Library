#pragma once

#include "Texture.hpp"
#include "Window.hpp"
#include "Widget.hpp"
#include "Vector2d.hpp"
#include "CompositeObject.hpp"

namespace SL
{
    class Container : public CompositeObject
    {
    public:

        Container(Vector2d shape, Vector2d position,  const Texture &texture = Texture(Color::Red)):
            CompositeObject(shape, position, texture)
            {}
    };
}
