#include "Window.h"

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
    for (int i = 0; i < main_window_->shape_.y_; i++)
    {
        for (int j = 0; j < main_window_->shape_.x_; j++)
        {
            texture_[i * (int)main_window_->shape_.x_ + j].color = main_window_->field_[i * (int)main_window_->shape_.x_ + j].get_sf_color();
        }
    }

    window_.draw(texture_, main_window_->shape_.x_ * main_window_->shape_.y_, sf::Points);
    window_.display();
}



void Window::clear(Color color)
{
    window_.clear(color.get_sf_color());
}