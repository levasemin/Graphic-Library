#pragma once
#include "ScrollVirtualWindow.h"
#include "ScrollBar.h"
#include "Color.h"
#include "Vector2d.h"
#include <vector>

class ScrollContainer : public ScrollVirtualWindow
{
public:

    ScrollContainer(Vector2d shape, Vector2d center, const Color &color = Colors::Red, VirtualWindow *parent = nullptr, std::vector<VirtualWindow *> children = {}) : 
        ScrollVirtualWindow(shape, center, color, parent, children)
    {
    };
};