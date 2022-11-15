#include "RenderTexture.h"
#include "Texture.h"
#include "Sprite.h"
#include "Window.h"
#include "Vector2d.h"

int main()
{
    Window window(Vector2d(720, 720));
    
    sf::RenderTexture render_texture;
    render_texture.create(100, 400);
    Texture texture(Colors::Blue);
    sf::Sprite sprite;
    sprite.setTexture(texture.texture_, true);
    sprite.setPosition(50, 50);
    render_texture.draw(sprite);
    sprite.setPosition(0, 0);
    sprite.setTexture(render_texture.getTexture(), true);
    render_texture.display();
    std::cout << sprite.getPosition().x << " " << sprite.getPosition().y;

    while (window.isOpen())
    {
        window.clear();

        window.draw(sprite);

        window.display();
    }
}