#pragma once

#include "Texture.h"
#include "Vector2d.h"
#include "CompositeObject.h"
#include "Widget.h"

class MainWindow : public CompositeObject
{
public:

    int style_;

    MainWindow(Vector2d shape, Texture texture, int style = sf::Style::Default):
        CompositeObject(shape, Vector2d(shape.x_ / 2, shape.y_ / 2), texture),
        style_(style)
    {
    }
    
    void exec()
    {

    }
};