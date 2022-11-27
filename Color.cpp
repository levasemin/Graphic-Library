#include "Color.h"

const Color Color::Black  ((uint8_t)0,   (uint8_t)0,   (uint8_t)0);
const Color Color::White  ((uint8_t)255, (uint8_t)255, (uint8_t)255);       
const Color Color::Red    ((uint8_t)255, (uint8_t)0,   (uint8_t)0);         
const Color Color::Green  ((uint8_t)0,   (uint8_t)255, (uint8_t)0);       
const Color Color::Blue   ((uint8_t)0,   (uint8_t)0,   (uint8_t)255);        
const Color Color::Yellow ((uint8_t)255, (uint8_t)255, (uint8_t)0);      
const Color Color::Magenta((uint8_t)255, (uint8_t)0,   (uint8_t)255);     
const Color Color::Cyan   ((uint8_t)0,   (uint8_t)255, (uint8_t)255);  

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
    g_rel_ *= color2.g_rel_;
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
    g_rel_ /= color2.g_rel_;
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

    claim();
}

void Color::set_h(const double &h)
{
    h_ = h;
    convert_hsv_rgb();
}
void Color::set_s(const double &s)
{
    s_ = s;
    convert_hsv_rgb();
}
void Color::set_v(const double &v)
{
    v_ = v;
    convert_hsv_rgb();
}

void Color::set_r(const uint8_t &r)
{
    r_rel_ = (double)r / 255.0;
    this->claim();

    convert_rgb_hsv();
}
void Color::set_g(const uint8_t &g)
{
    g_rel_ = (double)g / 255.0;
    this->claim();

    convert_rgb_hsv();
}
void Color::set_b(const uint8_t &b)
{
    b_rel_ = (double)b / 255.0;
    this->claim();

    convert_rgb_hsv();
}

double Color::get_h() const
{
    return h_;
}
double Color::get_s() const
{
    return s_;
}
double Color::get_v() const
{
    return v_;
}

uint8_t Color::get_r() const
{
    return r_;
}
uint8_t Color::get_g() const
{
    return g_;
}
uint8_t Color::get_b() const
{
    return b_;
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
    r_rel_ = (double)r / 255.0;
    g_rel_ = (double)g / 255.0;
    b_rel_ = (double)b / 255.0;

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
    r_rel_ = (double)r / 255.0;
    g_rel_ = (double)g / 255.0;
    b_rel_ = (double)b / 255.0;
    
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

    if (cmax == cmin)
        h_ = 0;
 
    else if (!doublecmp(cmax, r_rel_))
        h_ = fmod(60.0 * ((g_rel_ - b_rel_) / delta) + 360.0, 360.0);
 
    else if (!doublecmp(cmax, g_rel_))
        h_ = fmod(60.0 * ((b_rel_ - r_rel_) / delta) + 120.0, 360.0);
 
    else if (!doublecmp(cmax, b_rel_))
        h_ = fmod(60.0 * ((r_rel_ - g_rel_) / delta) + 240.0, 360.0);

    if (!doublecmp(cmax, 0))
        s_ = 0;
    else
        s_ = (delta / cmax);
 
    v_ = cmax;
}

/*
void Color::convert_rgb_hsv()
{
    double cmax = std::max(r_rel_, std::max(g_rel_, b_rel_));
    double cmin = std::min(r_rel_, std::min(g_rel_, b_rel_));

    v_ = cmax;

    s_ = cmax > 0 ? 1 - cmin / cmax : 0;
    
    if (g_ >= b_)
    {
        h_ = 1.0 / cos(((double)r_ - 0.5 * (double)g_ - 0.5 * (double)b_) / sqrt((double)std::pow(r_, 2) + (double)std::pow(g_, 2) + (double)std::pow(b_, 2) - (double)(r_ * g_ - r_ * b_ - g_ * b_)));
    }

    else
    {
        h_ = 360.0 - 1.0 / cos(((double)r_ - 0.5 * (double)g_ - 0.5 * (double)b_) / sqrt((double)std::pow(r_, 2) + (double)std::pow(g_, 2) + (double)std::pow(b_, 2) - (double)(r_ * g_ - r_ * b_ - g_ * b_)));
    }
}
*/
void Color::convert_hsv_rgb()
{
    double c = v_ * s_;
    double mod_2 = (fmod((h_ / 60.0), 2.0));
    double x = c * (1.0 - abs( mod_2 - 1.0));
    double m = v_ - c;
    double r = 0.0, g = 0.0, b = 0.0;

    if (h_ < 60.0)
    {
        r = c;
        g = x;
        b = 0.0;
    }

    else if (h_ < 120.0)
    {
        r = x;
        g = c;
        b = 0.0;
    }

    else if (h_ < 180.0)
    {
        r = 0.0;
        g = c;
        b = x;
    }

    else if (h_ < 240.0)
    {
        r = 0.0;
        g = x;
        b = c;
    }

    else if (h_ < 300.0)
    {
        r = x;
        g = 0.0;
        b = c;
    }

    else
    {
        r = c;
        g = 0.0;
        b = x;
    }
    
    r_ = (uint8_t)(round((r + m) * 255.0));
    g_ = (uint8_t)(round((g + m) * 255.0));
    b_ = (uint8_t)(round((b + m) * 255.0));
}

Color Color::convert_uint_color(uint32_t color)
{
    return Color((uint8_t)(color >> 24), (uint8_t)(color >> 16), (uint8_t)(color >> 8));
}
uint32_t Color::convert_color_uint(const Color &color)
{
    return ((uint32_t)color.get_r() << (uint32_t)24) + ((uint32_t)color.get_g() << (uint32_t)16) + ((uint32_t)color.get_b() << (uint32_t)8);
}