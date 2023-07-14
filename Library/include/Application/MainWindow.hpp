#pragma once

#include "Texture.hpp"
#include "CompositeObject.hpp"

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
            Resize     = sf::Style::Resize,
            Titlebar   = sf::Style::Titlebar,
        };

        MainWindow(Vector2d shape, Texture texture = Texture(Color::White), int style = sf::Style::Default);
    };
}