#pragma once

#include "Texture.h"
#include "Window.h"
#include "Widget.h"
#include "Vector2d.h"

class Container : public CompositeObject
{
public:

    Container(Vector2d shape, Vector2d center, const Texture &texture, Widget *parent = nullptr, const std::vector<Widget *> &children = {}): 
        CompositeObject(shape, center, texture, parent, children)
        {};
};