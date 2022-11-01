#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "functions.h"

class Color
{
private:
    double r_rel_, g_rel_, b_rel_;
    
public:
    int r_, g_, b_;
    Color(double r_rel, double g_rel, double b_rel);
    Color(int r, int g, int b); 
    Color(sf::Color color);
    Color(){};

    sf::Color get_sf_color() const;

    void print_color() const;

    void claim();
    
    void set_color(const int &r, const int &g, const int &b);
    void set_relation(const double &r_rel, const double &g_rel, const double &b_rel);
        
    void set_color_r(const int &r);
    void set_color_g(const int &g);
    void set_color_b(const int &b);

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

    friend Color operator + (const Color &color1,  const Color &color2);
    friend Color operator + (const Color &color,   const int &number);
    friend Color operator + (const int &number,    const Color &color);
    friend Color operator + (const Color &color,   const double &number);
    friend Color operator + (const double &number, const Color &color);

    friend Color operator - (const Color &color1, const Color &color2);
    friend Color operator - (const Color &color,  const int &number);
    friend Color operator - (const Color &color,  const double &number);

    friend Color operator * (const Color &color1, const Color &color2);
    friend Color operator * (const Color &color,  const int &number);
    friend Color operator * (const int &number,   const Color &color);
    friend Color operator * (const Color &color,  const double &number);
    friend Color operator * (const double &number,const Color &color);

    friend Color operator / (const Color &color1, const Color &color2);
    friend Color operator / (const Color &color,  const int &number);
    friend Color operator / (const Color &color,  const double &number);
};


namespace Colors
{
    static const Color Black(0, 0, 0);       
    static const Color White(255, 255, 255);       
    static const Color Red(255, 0, 0);         
    static const Color Green(0, 255, 0);       
    static const Color Blue(0, 0, 255);        
    static const Color Yellow(255, 255, 0);      
    static const Color Magenta(255, 0, 255);     
    static const Color Cyan(0, 255, 255);        
}