#pragma once

#include "Widget.h"
#include "Color.h"
#include "Vector2d.h"
#include "VirtualWindow.h"

class MainWindow : public VirtualWindow
{
public:

    int style_;

    MainWindow(Vector2d shape, Color color = Colors::White, int style = sf::Style::Default, std::vector<VirtualWindow *> children = {}):
        
        VirtualWindow(shape, Vector2d(shape.x_ / 2, shape.y_ / 2), color, nullptr, children),
        style_(style)
    {
    }
};