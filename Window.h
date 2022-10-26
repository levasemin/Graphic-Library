#pragma once

#include "MainWindow.h"
#include "Color.h"
#include <SFML/Graphics.hpp>

class Window
{

public:
    sf::RenderWindow window_;

    Window(MainWindow *main_window):
        window_(sf::VideoMode(main_window->width_, main_window->height_), "Vectors"),
        main_window_(main_window)
        {
            texture_ = (sf::Vertex *)calloc((main_window_->width_ * main_window_->height_), sizeof(sf::Vertex));
            for(int y = 0; y < main_window_->height_; y++)
            {
                for(int x = 0; x < main_window_->width_; x++)
                {
                    texture_[y * main_window_->width_ + x] = sf::Vertex(sf::Vector2f(x, y), sf::Color::Black);
                }
            } 
        };
    
    sf::Event event_;
    sf::Vertex *texture_ = nullptr;
    MainWindow *main_window_;

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