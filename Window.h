#pragma once

#include "Color.h"
#include <SFML/Graphics.hpp>
#include "Sprite.h"
#include "Event.h"

class Window
{

public:
    sf::RenderWindow window_;
    
    Window(Vector2d shape):
        window_(sf::VideoMode((uint32_t)shape.x_, (uint32_t)shape.y_), "Vectors")
        {
        };
        
    void draw(const sf::Vertex *vertices, std::size_t VertexCount, sf::PrimitiveType type, const sf::RenderStates &states = sf::RenderStates::Default);
    void draw(const sf::Drawable &drawable,                                                const sf::RenderStates &states = sf::RenderStates::Default);
    void draw(const sf::VertexBuffer &vertexBuffer,                                        const sf::RenderStates &states = sf::RenderStates::Default);	
    void draw(Sprite sprite);
    void clear();
    
    Window &operator =(const Window &that) = default;    
    
    bool isOpen();
    bool pollEvent(Event &event);
    void close();
    void display();
    void clear(Color color);
};