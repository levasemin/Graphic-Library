#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "functions.h"
#include <stdint.h>
#include <algorithm>

class Color
{ 
    uint8_t r_ = 0, g_ = 0, b_ = 0;
    float   h_ = 0, s_ = 0, v_ = 0;
public:
    Color(float h, float s, float v);
    Color(uint8_t r, uint8_t g, uint8_t b); 
    Color(sf::Color color);
    Color(){};

    sf::Color get_sf_color() const;

    static const Color Black;
    static const Color White;       
    static const Color Red;         
    static const Color Green;       
    static const Color Blue;   
    static const Color Grey;     
    static const Color Yellow;      
    static const Color Magenta;     
    static const Color Cyan;        

    void print_color() const;

    void claim();
    
    void set_color(const uint8_t &r, const uint8_t &g, const uint8_t &b);
    void set_relation(const float &r_rel, const float &g_rel, const float &b_rel);
        
    void set_r(const uint8_t &r);
    void set_g(const uint8_t &g);
    void set_b(const uint8_t &b);

    void set_h(const float &r);
    void set_s(const float &g);
    void set_v(const float &b);

    uint8_t get_r() const;
    uint8_t get_g() const;
    uint8_t get_b() const;

    float get_h() const;
    float get_s() const;
    float get_v() const;

    void set_relation_r(const float &r_rel);
    void set_relation_g(const float &g_rel);
    void set_relation_b(const float &b_rel);

    float get_relation_r();
    float get_relation_g();
    float get_relation_b();

    void pow(float degree);
    
    bool operator == (const Color &color2);
    bool operator != (const Color &color2);
    Color &operator += (const Color &color2);
    Color &operator += (const float &number);
    Color &operator -= (const Color &color2);
    Color &operator -= (const float &number);
    Color &operator *= (const Color &color2);
    Color &operator *= (const float &number);
    Color &operator /= (const Color &color2);
    Color &operator /= (const float &number);

    Color &operator =(const Color &that) = default;    

    void convert_hsv_rgb();
    void convert_rgb_hsv();

    static Color convert_uint_color(uint32_t color);
    static uint32_t convert_color_uint(const Color &color);

    friend Color operator + (const Color &color1,   const Color &color2);
    friend Color operator + (const Color &color,    const uint8_t &number);
    friend Color operator + (const uint8_t &number, const Color &color);
    friend Color operator + (const Color &color,    const float &number);
    friend Color operator + (const float &number,  const Color &color);

    friend Color operator - (const Color &color1, const Color &color2);
    friend Color operator - (const Color &color,  const uint8_t &number);
    friend Color operator - (const Color &color,  const float &number);

    friend Color operator * (const Color &color1, const Color &color2);
    friend Color operator * (const Color &color,  const uint8_t &number);
    friend Color operator * (const uint8_t &number,   const Color &color);
    friend Color operator * (const Color &color,  const float &number);
    friend Color operator * (const float &number,const Color &color);

    friend Color operator / (const Color &color1, const Color &color2);
    friend Color operator / (const Color &color,  const uint8_t &number);
    friend Color operator / (const Color &color,  const float &number);

private:
    float r_rel_ = 0, g_rel_ = 0, b_rel_ = 0;   
};