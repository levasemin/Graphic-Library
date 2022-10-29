#pragma once

#include "Texture.h"
#include "Window.h"
#include "Widget.h"
#include "Vector2d.h"

class Container : public VirtualWindow
{
public:

    Container(Vector2d shape, Vector2d center, const Texture &texture, VirtualWindow *parent = nullptr, const std::vector<VirtualWindow *> &widgets = {}): 
        VirtualWindow(shape, center, texture, parent)
        {};
};