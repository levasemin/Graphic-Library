#pragma once

#include "CompositeObject.hpp"

namespace SL
{
    /**
     * @brief class MainWindow is virtual window, the first object of Application.
     * 
     */
    class MainWindow : public CompositeObject
    {
    public:
        /**
         * @brief different styles of window
         */
        enum class Style
        {
            None       = sf::Style::None,       ///< No border / title bar (this flag and all others are mutually exclusive)
            Titlebar   = sf::Style::Titlebar,   ///< Title bar + fixed border
            Resize     = sf::Style::Resize,     ///< Title bar + resizable border + maximize button
            Close      = sf::Style::Close,      ///< Title bar + close button
            Fullscreen = sf::Style::Fullscreen, ///< Fullscreen mode (this flag and all others are mutually exclusive)
            Default    = sf::Style::Default,    ///< Default window style

        };

        /**
         * @brief Construct a new MainWindow object
         * 
         * @param shape 
         * @param texture 
         * @param style 
         */
        MainWindow(Vector2d shape, Texture texture = Texture(Color::White), Style style = Style::Default);

        MainWindow(const MainWindow &source) = default;
        MainWindow &operator=(const MainWindow &source) = default;
        ~MainWindow() = default;
        
        friend class Application;
    
    private:
        Style style_; ///< style of window
    };
}