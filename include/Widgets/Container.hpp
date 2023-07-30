#pragma once

#include "Texture.hpp"
#include "Window.hpp"
#include "CompositeObject.hpp"
#include "Vector2d.hpp"

namespace SL
{
    class Container : public CompositeObject
    {
    public:
        Container(Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::Red));

        Container(const Container &source) = default;
        Container &operator=(const Container &source) = default;
        ~Container() = default;
    };
}
