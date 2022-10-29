#pragma once
#include "ScrollVirtualWindow.h"
#include "ScrollBar.h"
#include "Vector2d.h"
#include <vector>

class ScrollContainer : public ScrollVirtualWindow
{
public:

    ScrollContainer(Vector2d shape, Vector2d center, const Texture &texture, VirtualWindow *parent = nullptr, std::vector<VirtualWindow *> children = {}) : 
        ScrollVirtualWindow(shape, center, texture, parent, children)
    {
    };
};