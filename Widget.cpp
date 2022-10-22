#include "Widget.h"

Widget::Widget(int wind_w, int wind_h, int style) : 
    window_(sf::VideoMode(wind_w, wind_h), "Vectors", style),
    wind_w_(wind_w),
    wind_h_(wind_h)
{
}


void Widget::draw(const sf::Drawable &drawable, const sf::RenderStates &states)
{
    window_.draw(drawable, states);
}	

void Widget::draw(const sf::Vertex *vertices, std::size_t VertexCount, sf::PrimitiveType type, const sf::RenderStates &states)
{
    window_.draw(vertices, VertexCount, type);
}

void Widget::draw(const sf::VertexBuffer &vertexBuffer, const sf::RenderStates &states)
{
    window_.draw(vertexBuffer, states);
}

bool Widget::isOpen()
{
    return window_.isOpen();
}


bool Widget::pollEvent(sf::Event event)
{
    return window_.pollEvent(event);
}


void Widget::close()
{
    window_.close();
}


void Widget::display()
{
    window_.display();
}


void Widget::clear(Color color)
{
    window_.clear(color.get_sf_color());
}