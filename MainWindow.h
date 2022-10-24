#include "Window.h"
#include <SFML/Graphics.hpp>

class MainWindow : public Window
{
public:
    Color color_;

    MainWindow(int width, int height, int style = sf::Style::Default, Color color = Colors::White) :  Window(width, height, style),  color_(color){};

    bool point_belonging(point point) override;
    void draw(Color *array, int app_width) override;
};

bool MainWindow::point_belonging(point point)
{
    return abs(point.x - center_.x) < width_ / 2 && abs(point.y - center_.y) < height_ / 2;
}

void MainWindow::draw(Color *array, int app_width)
{    
    point start = {center_.x - width_ / 2, center_.y - height_ / 2};
    point end   = {center_.x + width_ / 2, center_.y + height_ / 2};

    for (int i = start.y; i < end.y; i++)
    {
        for (int j = start.x; j < end.x; j++)
        {
            array[i * app_width + j] = color_;
        }
    }
}