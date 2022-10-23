#pragma once

#include "Widget.h"
#include "Event.h"
#include "Color.h"
#include <SFML/Graphics.hpp>

class Window
{

public:
    sf::RenderWindow window_;
    int wind_w_, wind_h_;

    Event<Window *, point> ClickLeftEvent_;
    Event<Window *, point> ClickRightEvent_;
    Event<Window *, int> PressKeyEvent_;

    Window(int wind_w, int wind_h, int style = sf::Style::Default) : 
        window_(sf::VideoMode(wind_w, wind_h), "Vectors", style),
        wind_w_(wind_w),
        wind_h_(wind_h)    
        {};

    void draw(const sf::Vertex *vertices, std::size_t VertexCount, sf::PrimitiveType type, const sf::RenderStates &states = sf::RenderStates::Default);
    void draw(const sf::Drawable &drawable,                                                const sf::RenderStates &states = sf::RenderStates::Default);
    void draw(const sf::VertexBuffer &vertexBuffer,                                        const sf::RenderStates &states = sf::RenderStates::Default);	
    void draw(const std::vector <Widget *> &widgets);

    Window &operator =(const Window &that) = default;    
    
    bool isOpen();
    bool pollEvent(sf::Event event);
    void close();
    void display();
    void clear(Color color);
};