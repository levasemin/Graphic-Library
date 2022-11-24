#include "Color.h"

bool Color::operator == (const Color &color2)
{
    return !(doublecmp(r_, color2.r_) || doublecmp(g_, color2.g_) || doublecmp(b_, color2.b_));
}

bool Color::operator != (const Color &color2)
{
    return doublecmp(r_, color2.r_) || doublecmp(g_, color2.g_) || doublecmp(b_, color2.b_);
}

Color &Color::operator += (const Color &color2)
{
    r_ += color2.r_;
    g_ += color2.g_;
    b_ += color2.b_;
    
    r_rel_ = r_ / 255.0;
    g_rel_ = g_ / 255.0;
    b_rel_ = b_ / 255.0;

    return *this;
}

Color &Color::operator += (const double &number)
{
    r_rel_ += number;
    g_rel_ += number;
    b_rel_ += number;

    r_ = r_rel_ * 255.0;
    g_ = g_rel_ * 255.0;
    b_ = b_rel_ * 255.0;

    return *this;
}

Color &Color::operator -= (const Color &color2)
{
    r_ -= color2.r_;
    g_ -= color2.g_;
    b_ -= color2.b_;

    r_rel_ = r_ / 255.0;
    g_rel_ = g_ / 255.0;
    b_rel_ = b_ / 255.0;

    return *this;
}

Color &Color::operator -= (const double &number)
{
    r_rel_ -= number;
    g_rel_ -= number;
    b_rel_ -= number;

    r_ = r_rel_ * 255.0;
    g_ = g_rel_ * 255.0;
    b_ = b_rel_ * 255.0;

    return *this;
}

Color &Color::operator *= (const Color &color2)
{
    r_rel_ *= color2.r_rel_;
    g_rel_ *= color2.r_rel_;
    b_rel_ *= color2.b_rel_;

    r_ = r_rel_ * 255.0;
    g_ = g_rel_ * 255.0;
    b_ = b_rel_ * 255.0;

    return *this;
}

Color &Color::operator *= (const double &number)
{
    r_rel_ *= number;
    g_rel_ *= number;
    b_rel_ *= number;

    r_ = r_rel_ * 255.0;
    g_ = g_rel_ * 255.0;
    b_ = b_rel_ * 255.0;

    return *this;
}

Color &Color::operator /= (const Color &color2)
{
    r_rel_ /= color2.r_rel_;
    g_rel_ /= color2.r_rel_;
    b_rel_ /= color2.b_rel_;

    r_ = r_rel_ * 255.0;
    g_ = g_rel_ * 255.0;
    b_ = b_rel_ * 255.0;

    return *this;
}

Color &Color::operator /= (const double &number)
{
    r_rel_ /= number;
    g_rel_ /= number;
    b_rel_ /= number;

    r_ = r_rel_ * 255.0;
    g_ = g_rel_ * 255.0;
    b_ = b_rel_ * 255.0;

    return *this;
}

Color operator + (const Color &color1, const Color &color2)
{
    Color new_color = std::move(color1);
    new_color += color2;

    return new_color;
}

Color operator + (const Color &color, const uint8_t &number)
{
    Color new_color = color;
    new_color += number;
    
    return new_color;
}

Color operator + (const uint8_t &number, const Color &color)
{
    Color new_color = color;
    new_color += number;
    
    return new_color;
}

Color operator + (const Color &color, const double &number)
{
    Color new_color = color;
    new_color += number;
    
    return new_color;
}

Color operator + (const double &number, const Color &color)
{
    Color new_color = color;
    new_color += number;
    
    return new_color;
}

Color operator - (const Color &color1, const Color &color2)
{
    Color new_color = color1;
    new_color -= color2;
    
    return new_color;
}

Color operator - (const Color &color, const uint8_t &number)
{
    Color new_color = color;
    new_color -= number;
    
    return new_color;
}

Color operator - (const Color &color, const double &number)
{
    Color new_color = color;
    new_color -= number;
    
    return new_color;
}

Color operator * (const Color &color1, const Color &color2)
{
    Color new_color = color1;
    new_color *= color2;
    
    return new_color;
}

Color operator * (const Color &color, const uint8_t &number)
{
    Color new_color = color;
    new_color *= number;
    
    return new_color;
}

Color operator * (const uint8_t &number, const Color &color)
{
    Color new_color = color;
    new_color *= number;
    
    return new_color;
}

Color operator * (const Color &color, const double &number)
{
    Color new_color = color;
    new_color *= number;
    
    return new_color;
}

Color operator * (const double &number, const Color &color)
{
    Color new_color = color;
    new_color *= number;
    
    return new_color;
}

Color operator / (const Color &color1, const Color &color2)
{
    Color new_color = color1;
    new_color /= color2;
    
    return new_color;
}

Color operator / (const Color &color, const uint8_t &number)
{
    Color new_color = color;
    new_color /= number;
    
    return new_color;
}

Color operator / (const Color &color, const double &number)
{
    Color new_color = color;
    new_color /= number;
    
    return new_color;
}

void Color::pow(double degree)
{
    r_rel_ = powf64(r_rel_, degree);
    g_rel_ = powf64(g_rel_, degree);
    b_rel_ = powf64(b_rel_, degree);
}

void Color::set_color_r(const uint8_t &r)
{
    r_rel_ = r / 255.0;
    this->claim();
}

void Color::set_color_g(const uint8_t &g)
{
    g_rel_ = g / 255.0;
    this->claim();
}

void Color::set_color_b(const uint8_t &b)
{
    b_rel_ = b / 255.0;
    this->claim();
}

void Color::set_relation_r(const double &r_rel)
{
    r_rel_ = r_rel;
    this->claim();
}

void Color::set_relation_g(const double &g_rel)
{
    g_rel_ = g_rel;
    this->claim();
}

void Color::set_relation_b(const double &b_rel)
{
    b_rel_ = b_rel;
    this->claim();
}

void Color::set_color(const uint8_t &r, const uint8_t &g, const uint8_t &b)
{
    r_rel_ = r / 255.0;
    g_rel_ = g / 255.0;
    b_rel_ = b / 255.0;

    this->claim();
}

void Color::set_relation(const double &r_rel, const double &g_rel, const double &b_rel)
{
    r_rel_ = r_rel;
    g_rel_ = g_rel;
    b_rel_ = b_rel;
    this->claim();

}

void Color::claim()
{
    r_rel_ = r_rel_ <= 1 ? r_rel_ : 1;
    g_rel_ = g_rel_ <= 1 ? g_rel_ : 1;
    b_rel_ = b_rel_ <= 1 ? b_rel_ : 1;

    r_rel_ = r_rel_ >= 0 ? r_rel_ : 0;
    g_rel_ = g_rel_ >= 0 ? g_rel_ : 0;
    b_rel_ = b_rel_ >= 0 ? b_rel_ : 0;

    r_ = uint8_t(r_rel_ * 255.0);
    g_ = uint8_t(g_rel_ * 255.0);
    b_ = uint8_t(b_rel_ * 255.0);
}

Color::Color (uint8_t r, uint8_t g, uint8_t b): r_(r), g_(g), b_(b)
{
    r_rel_ = r / 255.0;
    g_rel_ = g / 255.0;
    b_rel_ = b / 255.0;
    this->claim();
};

Color::Color (sf::Color color) : Color(color.r, color.g, color.b)
{}

Color::Color (double r_rel, double g_rel, double b_rel): r_rel_(r_rel), g_rel_(g_rel), b_rel_(b_rel)
{
    this->claim();
};

sf::Color Color::get_sf_color() const
{
    return sf::Color(r_, g_, b_);
}

void Color::print_color() const
{
    std::cout << (int)r_ << std::endl;
    std::cout << (int)g_ << std::endl;
    std::cout << (int)b_ << std::endl;
}