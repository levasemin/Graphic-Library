#pragma once

#include <iostream>

class Vector2d
{
public:
    double x_, y_;

    Vector2d(double x, double y): 
        x_(x),
        y_(y)
        {};

    void set_value(double x, double y);
    void print_value();

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