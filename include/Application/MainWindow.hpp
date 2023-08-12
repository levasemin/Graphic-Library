#pragma once

#include "CompositeObject.hpp"

namespace SL
{
    class MainWindow : public CompositeObject
    {
    public:
        enum class Style
        {
            None       = sf::Style::None,
            Titlebar   = sf::Style::Titlebar,
            Resize     = sf::Style::Resize,
            Close      = sf::Style::Close,
            Default    = sf::Style::Default,
            Fullscreen = sf::Style::Fullscreen,
        };

        MainWindow(Vector2d shape, Texture texture = Texture(Color::White), Style style = Style::Default);

        MainWindow(const MainWindow &source) = default;
        MainWindow &operator=(const MainWindow &source) = default;
        ~MainWindow() = default;
        
        friend class Application;
    
    private:
        Style style_;
    };
}