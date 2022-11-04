#pragma once

#include "MainWindow.h"
#include "Color.h"
#include <SFML/Graphics.hpp>
#include "Sprite.h"

class Window
{

public:
    sf::RenderWindow window_;

    Window(Widget *main_window):
        window_(sf::VideoMode(main_window->shape_.x_, main_window->shape_.y_), "Vectors"),
        main_window_(main_window)
        {
        };
    
    sf::Event event_;
    Widget *main_window_;

    void draw(const sf::Vertex *vertices, std::size_t VertexCount, sf::PrimitiveType type, const sf::RenderStates &states = sf::RenderStates::Default);
    void draw(const sf::Drawable &drawable,                                                const sf::RenderStates &states = sf::RenderStates::Default);
    void draw(const sf::VertexBuffer &vertexBuffer,                                        const sf::RenderStates &states = sf::RenderStates::Default);	
    void draw(Sprite sprite);
    void clear();
    
    Window &operator =(const Window &that) = default;    
    
    bool isOpen();
    bool pollEvent(sf::Event event);
    void close();
    void display();
    void clear(Color color);
};