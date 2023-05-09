#pragma once

#include "../Classes/Texture.h"
#include "../Classes/Vector2d.h"
#include "../Widget/CompositeObject.h"
#include "../Widget/Widget.h"

namespace SL
{
    class MainWindow : public CompositeObject
    {
    public:
        int style_;
        enum Style
        {
            Close      = sf::Style::Close,
            Default    = sf::Style::Default,
            Fullscreen = sf::Style::Fullscreen,
            None       = sf::Style::None,
            Resize     =  sf::Style::Resize,
            Titlebar   = sf::Style::Titlebar,
        };

        MainWindow(Vector2d shape, Texture texture, int style = sf::Style::Default):
            CompositeObject(shape, Vector2d(0, 0), texture),
            style_(style)
        {
        }
    };
}