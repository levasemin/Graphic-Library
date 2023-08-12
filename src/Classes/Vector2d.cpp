#include "Vector2d.hpp"

namespace SL
{
    sf::Vector2u Vector2d::to_sf_vector() const
    {
        return sf::Vector2u(static_cast<uint32_t>(x_), static_cast<uint32_t>(y_));
    }

    void Vector2d::print_value() const
    {
        std::cout << x_ << std::endl;
        std::cout << y_ << std::endl << std::endl;
    }
    
    Vector2d operator + (const Vector2d &first, const Vector2d &second)
    {
        Vector2d new_vector = first;
        new_vector += second;
        return new_vector;
    }

    Vector2d operator + (const Vector2d &first, float num)
    {
        Vector2d new_vector = first;
        new_vector.x_ += num;
        new_vector.y_ += num;
        return new_vector;
    }

    Vector2d operator + (float num, const Vector2d &first)
    {
        Vector2d new_vector = first;
        new_vector.x_ += num;
        new_vector.y_ += num;
        return new_vector;
    }

    Vector2d operator - (const Vector2d &first, const Vector2d &second)
    {
        Vector2d new_vector = first;
        new_vector -= second;
        return new_vector;
    }

    Vector2d operator - (const Vector2d &first, float num)
    {
        Vector2d new_vector = first;
        new_vector.x_ -= num;
        new_vector.y_ -= num;
        return new_vector;
    }

    Vector2d operator * (const Vector2d &that, float num)
    {
        Vector2d new_vector = that;
        new_vector *= num;
        return new_vector;
    }

    Vector2d operator * (float num, const Vector2d &that)
    {
        Vector2d new_vector = that;
        new_vector *= num;
        return new_vector;
    }

    Vector2d operator / (const Vector2d &that, float num)
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

    Vector2d &Vector2d::operator *= (float num)
    {
        x_ *= num;
        y_ *= num;

        return *this;
    }

    Vector2d &Vector2d::operator /= (float num)
    {
        x_ /= num;
        y_ /= num;

        return *this;
    }
}