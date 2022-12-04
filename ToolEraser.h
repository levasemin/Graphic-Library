#pragma once

#include "Command.h"
#include "Color.h"
#include "Circle.h"
#include <deque>
#include "tools.h"

class ToolEraser : public booba::Tool
{

public:
    struct point
    {
        float x;
        float y;
    }; 

    class Interpolator
    {
    public:
        int type_ = 0;

        static const int CATMULL_ROM = 0;

        Interpolator(int type):
            type_(type)
        {

        }
        
        ToolEraser::point operator()(float t, ToolEraser::point point_0, ToolEraser::point point_1, ToolEraser::point point_2, ToolEraser::point point_3)
        {
            ToolEraser::point new_point = {0.f, 0.f};

            if (type_ == CATMULL_ROM)
            {
                float coeff_0 = -t * pow(1.f - t, 2.f);
                float coeff_1 = (2.f - 5.f*pow(t, 2.f) + 3.f*pow(t, 3.f));
                float coeff_2 = t * (1.f + 4.f*t - 3.f*pow(t, 2.f));
                float coeff_3 = pow(t, 2.f) * (1.f - t);

                new_point.x = 0.5f * (coeff_0 * point_0.x + coeff_1 * point_1.x + coeff_2 * point_2.x - coeff_3 * point_3.x);
                new_point.y = 0.5f * (coeff_0 * point_0.y + coeff_1 * point_1.y + coeff_2 * point_2.y - coeff_3 * point_3.y);
            }

            return new_point;
        }
    };

    bool clicked_ = false;
    char icon_path_[128] = "source/Eraser.png";

    Interpolator interpolator_;
    uint64_t width_scroll_bar_   = (uint64_t)nullptr;
    uint64_t settings_container_ = (uint64_t)nullptr;

    std::deque<point> points_;

    Circle drawing_object_;
    
    ToolEraser() : Tool(),
        interpolator_(Interpolator::CATMULL_ROM),
        points_({}),
        drawing_object_(1.f, Color::White)
    {         
        booba::addTool(this);
        buildSetupWidget();
    }

    ToolEraser(const ToolEraser &) = default;
    ToolEraser &operator=(const ToolEraser &) = default;

    void paint(booba::Image *image);

    void apply(booba::Image* image, const booba::Event* event) override;

    const char* getTexture() override
    {
        return icon_path_;
    } 

    void buildSetupWidget() override
    {
        width_scroll_bar_ = (uint64_t)booba::createScrollbar(100, 100, 200, 30);
    }
};