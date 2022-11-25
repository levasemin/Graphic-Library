#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "functions.h"
#include <stdint.h>

class Color
{ 
public:
    uint8_t r_, g_, b_;
    
    Color(double r_rel, double g_rel, double b_rel);
    Color(uint8_t r, uint8_t g, uint8_t b); 
    Color(sf::Color color);
    Color(){};

    sf::Color get_sf_color() const;

    void print_color() const;

    void claim();
    
    void set_color(const uint8_t &r, const uint8_t &g, const uint8_t &b);
    void set_relation(const double &r_rel, const double &g_rel, const double &b_rel);
        
    void set_color_r(const uint8_t &r);
    void set_color_g(const uint8_t &g);
    void set_color_b(const uint8_t &b);

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

    static Color convert_hsv_rgb(float h, float s, float v);

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


namespace Colors
{
    static const Color Black  ((uint8_t)0,   (uint8_t)0,   (uint8_t)0);       
    static const Color White  ((uint8_t)255, (uint8_t)255, (uint8_t)255);       
    static const Color Red    ((uint8_t)255, (uint8_t)0,   (uint8_t)0);         
    static const Color Green  ((uint8_t)0,   (uint8_t)255, (uint8_t)0);       
    static const Color Blue   ((uint8_t)0,   (uint8_t)0,   (uint8_t)255);        
    static const Color Yellow ((uint8_t)255, (uint8_t)255, (uint8_t)0);      
    static const Color Magenta((uint8_t)255, (uint8_t)0,   (uint8_t)255);     
    static const Color Cyan   ((uint8_t)0,   (uint8_t)255, (uint8_t)255);        
}