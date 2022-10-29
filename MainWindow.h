#pragma once

#include "Widget.h"
#include "Texture.h"
#include "Vector2d.h"
#include "VirtualWindow.h"

class MainWindow : public VirtualWindow
{
public:

    int style_;

    MainWindow(Vector2d shape, Texture texture, int style = sf::Style::Default, std::vector<VirtualWindow *> children = {}):
        VirtualWindow(shape, Vector2d(shape.x_ / 2, shape.y_ / 2), texture, nullptr, children),
        style_(style)
    {
    }
};