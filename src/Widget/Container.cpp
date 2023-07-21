#include "Container.hpp"

namespace SL
{
    Container::Container(Vector2d shape, Vector2d position, const Texture &texture):
        CompositeObject(shape, position, texture)
        {}
}