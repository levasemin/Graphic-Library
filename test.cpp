#include <vector>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "RenderTexture.h"
#include "Texture.h"
#include "Sprite.h"
#include "Vector2d.h"
#include "Color.h"

const char *path_britsih = "/home/levce/projectsDED/event_handler2/Event_handler/source/british.jpg";

int main()
{
    sf::Texture tex;
    tex.loadFromFile(path_britsih);
    sf::Sprite sprite;
    sprite.setTexture(tex);
                                                                             
    sprite.setTextureRect(sf::IntRect(100, 200, 450, 600));
    std::cout << sprite.getTextureRect().width;
}