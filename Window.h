#pragma once

#include "VirtualWindow.h"
#include "Color.h"
#include <SFML/Graphics.hpp>

class Window
{

public:
    sf::RenderWindow window_;

    Window(VirtualWindow *main_window):
        window_(sf::VideoMode(main_window->shape_.x_, main_window->shape_.y_), "Vectors"),
        main_window_(main_window)
        {
            texture_ = (sf::Vertex *)calloc((main_window->shape_.x_ * main_window->shape_.y_), sizeof(sf::Vertex));
            for(int y = 0; y < main_window->shape_.y_; y++)
            {
                for(int x = 0; x < main_window->shape_.x_; x++)
                {
                    texture_[y * (int)main_window->shape_.x_ + x] = sf::Vertex(sf::Vector2f(x, y), sf::Color::Black);
                }
            } 
        };
    
    sf::Event event_;
    sf::Vertex *texture_ = nullptr;
    VirtualWindow *main_window_;

    void draw(const sf::Vertex *vertices, std::size_t VertexCount, sf::PrimitiveType type, const sf::RenderStates &states = sf::RenderStates::Default);
    void draw(const sf::Drawable &drawable,                                                const sf::RenderStates &states = sf::RenderStates::Default);
    void draw(const sf::VertexBuffer &vertexBuffer,                                        const sf::RenderStates &states = sf::RenderStates::Default);	
    void draw(const Color *field);

    Window &operator =(const Window &that) = default;    
    
    bool isOpen();
    bool pollEvent(sf::Event event);
    void close();
    void display();
    void clear(Color color);
};