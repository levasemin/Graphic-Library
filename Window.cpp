#include "Window.h"

void Window::draw(const std::vector<Widget *> &widgets)
{
    for (int i = 0; i < widgets.size(); i++)
    {
        widgets[i]->draw(field_, wind_w_);
    }
}


void Window::draw(const sf::Drawable &drawable, const sf::RenderStates &states)
{
    window_.draw(drawable, states);
}	


void Window::draw(const sf::Vertex *vertices, std::size_t VertexCount, sf::PrimitiveType type, const sf::RenderStates &states)
{
    window_.draw(vertices, VertexCount, type);
}


void Window::draw(const sf::VertexBuffer &vertexBuffer, const sf::RenderStates &states)
{
    window_.draw(vertexBuffer, states);
}


bool Window::isOpen()
{
    return window_.isOpen();
}



bool Window::pollEvent(sf::Event event)
{
    return window_.pollEvent(event);
}



void Window::close()
{
    window_.close();
}



void Window::display()
{
    for (int i = 0; i < wind_h_; i++)
    {
        for (int j = 0; j < wind_w_; j++)
        {
            texture_[i * wind_w_ + j].color = field_[i * wind_w_ + j].get_sf_color();
        }
    }

    //field_[30 * wind_w_ + 30].print_color();
    //std::cout << wind_h_ << " " << wind_w_ << std::endl;
    window_.draw(texture_, wind_w_ * wind_h_, sf::Points);
    window_.display();
}



void Window::clear(Color color)
{
    window_.clear(color.get_sf_color());
}