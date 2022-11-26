#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "functions.h"
#include <stdint.h>
#include <algorithm>

class Color
{ 
    uint8_t r_, g_, b_;
    double h_, s_, v_;
public:
    Color(double h, double s, double v);
    Color(uint8_t r, uint8_t g, uint8_t b); 
    Color(sf::Color color);
    Color(){};

    sf::Color get_sf_color() const;

    static const Color Black;
    static const Color White;       
    static const Color Red;         
    static const Color Green;       
    static const Color Blue;        
    static const Color Yellow;      
    static const Color Magenta;     
    static const Color Cyan;        

    void print_color() const;

    void claim();
    
    void set_color(const uint8_t &r, const uint8_t &g, const uint8_t &b);
    void set_relation(const double &r_rel, const double &g_rel, const double &b_rel);
        
    void set_r(const uint8_t &r);
    void set_g(const uint8_t &g);
    void set_b(const uint8_t &b);

    void set_h(const double &r);
    void set_s(const double &g);
    void set_v(const double &b);

    uint8_t get_r() const;
    uint8_t get_g() const;
    uint8_t get_b() const;

    double get_h() const;
    double get_s() const;
    double get_v() const;

    void set_relation_r(const double &r_rel);
    void set_relation_g(const double &g_rel);
    void set_relation_b(const double &b_rel);

    void pow(double degree);
    
    bool operator == (const Color &color2);
    bool operator != (const Color &color2);
    Color &operator += (const Color &color2);
    Color &operator += (const double &number);
    Color &operator -= (const Color &color2);
    Color &operator -= (const double &number);
    Color &operator *= (const Color &color2);
    Color &operator *= (const double &number);
    Color &operator /= (const Color &color2);
    Color &operator /= (const double &number);

    Color &operator =(const Color &that) = default;    

    void convert_hsv_rgb();
    void convert_rgb_hsv();

    friend Color operator + (const Color &color1,   const Color &color2);
    friend Color operator + (const Color &color,    const uint8_t &number);
    friend Color operator + (const uint8_t &number, const Color &color);
    friend Color operator + (const Color &color,    const double &number);
    friend Color operator + (const double &number,  const Color &color);

    friend Color operator - (const Color &color1, const Color &color2);
    friend Color operator - (const Color &color,  const uint8_t &number);
    friend Color operator - (const Color &color,  const double &number);

    friend Color operator * (const Color &color1, const Color &color2);
    friend Color operator * (const Color &color,  const uint8_t &number);
    friend Color operator * (const uint8_t &number,   const Color &color);
    friend Color operator * (const Color &color,  const double &number);
    friend Color operator * (const double &number,const Color &color);

    friend Color operator / (const Color &color1, const Color &color2);
    friend Color operator / (const Color &color,  const uint8_t &number);
    friend Color operator / (const Color &color,  const double &number);

private:
    double r_rel_, g_rel_, b_rel_;   
};