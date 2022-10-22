#pragma once
#include "Event.h"
#include "Color.h"
#include <SFML/Graphics.hpp>

class Widget
{

public:
    sf::RenderWindow window_;
    int wind_w_, wind_h_;

    Widget(int wind_w, int wind_h, int style = sf::Style::Default);    
        
    void draw(const sf::Vertex *vertices, std::size_t VertexCount, sf::PrimitiveType type, const sf::RenderStates &states = sf::RenderStates::Default);
    void draw(const sf::Drawable &drawable,                                                const sf::RenderStates &states = sf::RenderStates::Default);
    void draw(const sf::VertexBuffer &vertexBuffer,                                        const sf::RenderStates &states = sf::RenderStates::Default);	
    
    Widget &operator =(const Widget &that) = default;    

    bool isOpen();
    bool pollEvent(sf::Event event);
    void close();
    void display();
    void clear(Color color);
};