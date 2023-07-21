#pragma once

#include "../Rendering/Texture.hpp"
#include "../Application/Window.hpp"
#include "../BaseWidget/BaseWidget.hpp"
#include "../Classes/Vector2d.hpp"

namespace SL
{
    class Container : public CompositeObject
    {
    public:
        Container(Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::Red));
    };
}
