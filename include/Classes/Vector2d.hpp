#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace SL
{
    class Vector2d
    {
    public:
        float x_, y_;

        Vector2d(float x = 0, float y = 0): 
            x_(x),
            y_(y)
            {};

        Vector2d(int x, int y): 
            x_(static_cast<float>(x)),
            y_(static_cast<float>(y))
            {};
        
        Vector2d(uint32_t x, uint32_t y): 
            x_(static_cast<float>(x)),
            y_(static_cast<float>(y))
            {};

        Vector2d(size_t x, size_t y): 
            x_(static_cast<float>(x)),
            y_(static_cast<float>(y))
            {};

        Vector2d(sf::Vector2u sf_vector):
            x_(static_cast<float>(sf_vector.x)),
            y_(static_cast<float>(sf_vector.y))
        {}

        Vector2d(sf::Vector2f sf_vector):
            x_(sf_vector.x),
            y_(sf_vector.y)
        {}

        Vector2d(const Vector2d &source) = default;
        Vector2d &operator= (const Vector2d &source) = default;
        ~Vector2d() = default;
        
        sf::Vector2u to_sf_vector() const;
        void print_value () const;

        friend Vector2d operator + (const Vector2d &first, const Vector2d &second);
        friend Vector2d operator + (float num, const Vector2d &first);
        friend Vector2d operator + (const Vector2d &first, float num);
        friend Vector2d operator - (const Vector2d &first, const Vector2d &second);
        friend Vector2d operator - (const Vector2d &first, float num);
        friend Vector2d operator * (const Vector2d &first, float num);
        friend Vector2d operator * (float num, const Vector2d &first);
        friend Vector2d operator / (const Vector2d &first, float num);
        
        Vector2d &operator -= (const Vector2d &that);
        Vector2d &operator += (const Vector2d &that);
        Vector2d &operator *= (float num);
        Vector2d &operator /= (float num);
    };
}