#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once
#include <SFML/Graphics.hpp>

#include "Color.hpp"
#include "Sprite.hpp"
#include "Event.hpp"

namespace SL
{
    /**
     * @brief class Window is wrapper over sfml window.
     * @details you will never create object of this class, you will just create and change MainWindow 
     *          and open it by Application in new window. 
     */
    class Window
    {
        sf::RenderWindow window_;
        bool visible_ = true;

        Window(Vector2d shape, int style = 7);        
        Window (const Window &source) = default;
        Window &operator =(const Window &source) = default;
        ~Window() = default;

        bool getVisible();
        void setVisible(bool visible);
        void draw(Sprite sprite);
        void clear();
        
        void create(Vector2d shape, std::string name, int style);
        bool isOpen();
        bool pollEvent(Event &event);
        void close();
        void display();
        void clear(Color color);

        friend class Application;
        friend class Object;
    };
};