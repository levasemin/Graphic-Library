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

    convert_rgb_hsv();
};

Color::Color (sf::Color color) : Color(color.r, color.g, color.b)
{}

Color::Color (double h, double s, double v): h_(h), s_(s), v_(v)
{
    convert_hsv_rgb();

    r_rel_ = r_ / 255.0;
    g_rel_ = g_ / 255.0;
    b_rel_ = b_ / 255.0;
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

void Color::convert_rgb_hsv()
{
    double cmax = std::max(r_rel_, std::max(g_rel_, b_rel_));
    double cmin = std::min(r_rel_, std::min(g_rel_, b_rel_));

    double delta = cmax - cmin;

    v_ = (cmax + cmin) / 2;

    if (delta == 0)
    {
        h_ = 0;
        s_ = 0;
    }

    else
    {
        if (cmax == r_rel_)
        {
            h_ = 60.0 * ((int)((g_rel_ - b_rel_ ) / delta * 10000.0) % 60000) / 10000.0;
        }

        else if (cmax == g_rel_)
        {
            h_ = 60 * ((b_rel_ - r_rel_) / delta + 2);
        }

        else if (cmax == b_rel_)
        {
            h_ = 60 * ((r_rel_ - g_rel_) / delta + 4);
        }

        s_ = delta / (1 - abs(2 * v_ - 1));
    }
}

void Color::convert_hsv_rgb()
{
    double c = v_ * s_;
    double mod_2 = (double)((int)(h_ / 60.0 * 10000.0) % 20000) / 10000.0;
    double x = c * (1 - abs( mod_2 - 1));
    double m = v_ - c;
    double r = 0, g = 0, b = 0;

    if (h_ < 60)
    {
        r = c;
        g = x;
        b = 0;
    }

    else if (h_ < 120)
    {
        r = x;
        g = c;
        b = 0;
    }

    else if (h_ < 180)
    {
        r = 0;
        g = c;
        b = x;
    }

    else if (h_ < 240)
    {
        r = 0;
        g = x;
        b = c;
    }

    else if (h_ < 300)
    {
        r = x;
        g = 0;
        b = c;
    }

    else
    {
        r = c;
        g = 0;
        b = x;
    }
    
    r_ = (uint8_t)(int)((r + m) * 255.0);
    g_ = (uint8_t)(int)((g + m) * 255.0);
    b_ = (uint8_t)(int)((b + m) * 255.0);
}
