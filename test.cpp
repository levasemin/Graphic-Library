#include "SFML/Graphics.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(720, 720), "Vectors");
    sf::RenderTexture render_texture;
    render_texture.create(50, 100);
    sf::Sprite sprite;
    sf::Texture texture;
    
    sf::Image image;
    image.create(100, 100, sf::Color::Blue);
    texture.loadFromImage(image);
    
    sprite.setTexture(texture);

    render_texture.draw(sprite);

    std::cout << render_texture.getTexture().getSize().x << " " << render_texture.getTexture().getSize().y << std::endl;
    
    sprite.setTexture(render_texture.getTexture(), false);

    std::cout << render_texture.getSize().x << " " << render_texture.getSize().y;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                window.close();
                break;
            }          
        }

        window.clear();

        window.draw(sprite);

        window.display();
    }
}