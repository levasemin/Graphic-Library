#pragma once
#include "ScrollWidget.h"
#include "ScrollBar.h"
#include "Vector2d.h"
#include <vector>

class ScrollContainer : public ScrollWidget
{
public:

    ScrollContainer(Vector2d shape, Vector2d center, const Texture &texture, Widget *parent = nullptr, std::vector<Widget *> children = {}) : 
        ScrollWidget(shape, center, texture, parent, children)
    {
    };
};