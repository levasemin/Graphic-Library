#pragma once

#include "Widget.h"
#include "Event.h"
#include "Color.h"
#include <SFML/Graphics.hpp>
#include "MainWindow.h"

class Window : public Widget
{

public:
    sf::RenderWindow window_;
    int wind_w_, wind_h_;

    Color *field_;
    sf::Vertex *texture_;

    Window(int wind_w, int wind_h, int style = sf::Style::Default) : 
        Widget({wind_w / 2, wind_h / 2}, wind_w, wind_h, nullptr),
        window_(sf::VideoMode(wind_w, wind_h), "Vectors", style),
        wind_w_(wind_w),
        wind_h_(wind_h)    
        {
            field_   = (Color *)calloc(wind_w * wind_h, sizeof(Color));
            texture_ = (sf::Vertex *)calloc((wind_w * wind_h), sizeof(sf::Vertex));
            for(int y = 0; y < wind_h; y++)
            {
                for(int x = 0; x < wind_w; x++)
                {
                    texture_[y * wind_w + x] = sf::Vertex(sf::Vector2f(x, y), sf::Color::Black);
                }
            } 
        };

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