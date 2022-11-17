#include "SFML/Graphics.hpp"
#include <iostream>

int main()
{
    sf::Window window(sf::VideoMode(720, 720), "OK");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::MouseMoved:
                printf("%d %d\n", event.mouseButton.x, event.mouseButton.y);
                break;
            
            default:
                break;
            }
        }
    }
}