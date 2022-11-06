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


void Window::draw(Sprite sprite)
{
    window_.draw(sprite.sprite_);
}

void Window::close()
{
    window_.close();
}


void Window::display()
{
    // main_window_->render_texture_->display();
    // Sprite sprite(main_window_->shape_, main_window_->render_texture_->getTexture());    
    
    // draw(sprite);
    window_.display();
}

void Window::clear()
{
    window_.clear();
}

void Window::clear(Color color)
{
    window_.clear(color.get_sf_color());
}