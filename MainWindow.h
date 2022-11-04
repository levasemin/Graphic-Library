#pragma once

#include "Texture.h"
#include "Vector2d.h"
#include "CompositeWidget.h"

class MainWindow : public CompositeWidget
{
public:

    int style_;

    MainWindow(Vector2d shape, Texture texture, int style = sf::Style::Default, std::vector<Widget *> children = {}):
        CompositeWidget(shape, Vector2d(shape.x_ / 2, shape.y_ / 2), texture, nullptr, children),
        style_(style)
    {
    }
};