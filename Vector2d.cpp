#include "Vector2d.h"

void Vector2d::print_value()
{
    std::cout << x_ << std::endl;
    std::cout << y_ << std::endl << std::endl;
}

void Vector2d::set_value(double x, double y)
{
    x_ = x;
    y_ = y;
}

Vector2d operator + (const Vector2d &first, const Vector2d &second)
{
    Vector2d new_vector = first;
    new_vector += second;
    return new_vector;
}

Vector2d operator - (const Vector2d &first, const Vector2d &second)
{
    Vector2d new_vector = first;
    new_vector -= second;
    return new_vector;
}

Vector2d operator * (const Vector2d &that, double num)
{
    Vector2d new_vector = that;
    new_vector *= num;
    return new_vector;
}

Vector2d operator * (double num, const Vector2d &that)
{
    return that * num;
}

Vector2d operator / (const Vector2d &that, double num)
{
    Vector2d new_vector = that;
    new_vector /= num;
    return new_vector;
}

Vector2d &Vector2d::operator -= (const Vector2d &that)
{
    x_ -= that.x_;
    y_ -= that.y_;

    return *this;
}

Vector2d &Vector2d::operator+= (const Vector2d &that)
{
    x_ += that.x_;
    y_ += that.y_;

    return *this;
}

Vector2d &Vector2d::operator *= (double num)
{
    x_ *= num;
    y_ *= num;

    return *this;
}

Vector2d &Vector2d::operator /= (double num)
{
    x_ /= num;
    y_ /= num;

    return *this;
}

