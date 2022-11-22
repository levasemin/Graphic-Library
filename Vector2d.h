#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Vector2d
{
public:
    double x_, y_;

    Vector2d(double x = 0, double y = 0): 
        x_(x),
        y_(y)
        {};

    Vector2d(sf::Vector2u sf_vector):
        x_(sf_vector.x),
        y_(sf_vector.y)
    {}

    Vector2d(sf::Vector2f sf_vector):
        x_(sf_vector.x),
        y_(sf_vector.y)
    {}

    sf::Vector2u to_sf_vector() const;
    void set_value(double x, double y);
    void print_value () const;

    friend Vector2d operator + (const Vector2d &first, const Vector2d &second);
    friend Vector2d operator - (const Vector2d &first, const Vector2d &second);
    friend Vector2d operator * (const Vector2d &first, double num);
    friend Vector2d operator * (double num, const Vector2d &first);
    friend Vector2d operator / (const Vector2d &first, double num);
    Vector2d &operator -= (const Vector2d &that);
    Vector2d &operator += (const Vector2d &that);
    Vector2d &operator *= (double num);
    Vector2d &operator /= (double num);
};