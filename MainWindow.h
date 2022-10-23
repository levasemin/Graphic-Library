#include "Window.h"
#include <SFML/Graphics.hpp>

class MainWindow : public Window
{
public:
    MainWindow(int width, int height, int style = sf::Style::Default) : Window(width, height, style) {};
};