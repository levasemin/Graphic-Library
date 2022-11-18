#include <iostream>
#include <stdlib.h>
#include "SFML/Graphics.hpp"

int main()
{
    sf::Window window(sf::VideoMode(720, 720), "A");

    int i = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event));
        {
            if (sf::Event::MouseButtonPressed == event.type)
            {
                printf("%d\n", i++);
            }
        }
    }
}