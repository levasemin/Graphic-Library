#include "Sprite.h"
#include "RenderTexture.h"
#include "Texture.h"
#include "Color.h"

const char *path_britsih = "/home/levce/projectsDED/event_handler2/Event_handler/source/british.jpg";

int main()
{
    sf::RenderWindow window(sf::VideoMode(720, 720), "sfd");
    RenderTexture render_texture(Vector2d(720, 720));

    Texture texture_(path_britsih);
    
    Vector2d shape_(100, 400);

    Vector2d start_field_(200, 0);
    Vector2d end_field_(300, 200);

    Sprite sprite_(shape_, Texture(path_britsih));

    Vector2d center_(250, 50);

    sprite_.setPosition(start_field_);
    
    Vector2d start(start_field_.x_ - (center_.x_ - shape_.x_ / 2), start_field_.y_ - (center_.y_ - shape_.y_ / 2));
    Vector2d end(  end_field_.x_   - (center_.x_ - shape_.x_ / 2), end_field_.y_   - (center_.y_ - shape_.y_ / 2));

    double x_coeff = 795.0  / shape_.x_;
    double y_coeff = 1200.0 / shape_.y_; 
    
    if (x_coeff > 1)
    {
        start.x_ *= x_coeff;
        end.x_   *= x_coeff;
    }

    if (y_coeff > 1)
    {
        start.y_ *= y_coeff;
        end.y_   *= y_coeff;
    }

    start.print_value();
    end.print_value();
    
    sprite_.setTextureRect(Vector2d(0, 450), Vector2d(795, 1050));

    printf("!%f %f!\n", sprite_.sprite_.getScale().x, sprite_.sprite_.getScale().y);
    
    render_texture.render_texture_.clear();
    render_texture.draw(sprite_);
    render_texture.display();
    
    Sprite render_sprite(Vector2d(720, 720), Texture(render_texture.getTexture()));
    
    sf::Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                {
                    return 0;
                }
            }
        }
        window.clear();
        window.draw(render_sprite.sprite_);

        window.display();
    }
}