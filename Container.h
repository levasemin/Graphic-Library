#pragma once

#include "Color.h"
#include "Window.h"
#include "Widget.h"
#include "Vector2d.h"

class Container : public VirtualWindow
{
public:

    Container(Vector2d shape, Vector2d center, const Color &color = Colors::Red, VirtualWindow *parent = nullptr, const std::vector<VirtualWindow *> &widgets = {}): 
        VirtualWindow(shape, center, color, parent)
        {};
};