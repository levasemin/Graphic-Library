#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once
#include <SFML/Graphics.hpp>

#include "Color.hpp"
#include "Sprite.hpp"
#include "Event.hpp"

namespace SL
{
    class Window
    {
        sf::RenderWindow window_;
        bool visible_ = true;

        Window(Vector2d shape, int style = 7);
        
        bool getVisible();
        void setVisible(bool visible);
        void draw(const sf::Vertex *vertices, std::size_t VertexCount, sf::PrimitiveType type, const sf::RenderStates &states = sf::RenderStates::Default);
        void draw(const sf::Drawable &drawable,                                                const sf::RenderStates &states = sf::RenderStates::Default);
        void draw(const sf::VertexBuffer &vertexBuffer,                                        const sf::RenderStates &states = sf::RenderStates::Default);	
        void draw(Sprite sprite);
        void clear();
        
        Window (const Window &source);

        Window &operator =(const Window &source);
        
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