#include "RenderTexture.h"
#include "Texture.h"
#include "Sprite.h"
#include "Window.h"
#include "Vector2d.h"

int main()
{
    Window window(Vector2d(720, 720));
    
    RenderTexture render_texture(Vector2d(100, 400));
    Texture texture("/home/levce/projectsDED/event_handler2/Event_handler/source/british.jpg");
    Sprite sprite(Vector2d(100, 400), texture);

    render_texture.draw(sprite);
    render_texture.display();
    sprite.setTexture(render_texture.getTexture());
    sprite.setPosition(Vector2d(650, 200));
    RenderTexture render_texture_wind(Vector2d(700, 700));
    Texture texture_wind(Colors::Yellow);
    Sprite sprite_wind(Vector2d(700, 700), texture_wind);

    render_texture.draw(sprite_wind);
    sprite_wind.setTexture(render_texture.getTexture());
    render_texture_wind.draw(sprite_wind);
    render_texture_wind.draw(sprite);
    
    render_texture_wind.display();
    sprite_wind.setTexture(render_texture_wind.getTexture());

    std::cout << render_texture.getSize().x_ << " " << render_texture.getSize().y_;

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

        window.draw(sprite_wind);

        window.display();
    }
}