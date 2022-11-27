#pragma once

#include "Tool.h"
#include "Command.h"
#include "ToolCommand.h"
#include "ToolManager.h"
#include "Color.h"
#include "HSVwindow.h"
#include <deque>

uint64_t createButton   (int32_t x, int32_t y, uint32_t w, uint32_t h, const char* object);

int CATMULL_ROM = 0;


class ToolPaint : public Tool
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

        Interpolator(int type):
            type_(type)
        {

        }

        ToolPaint::point operator()(float t, ToolPaint::point point_0, ToolPaint::point point_1, ToolPaint::point point_2, ToolPaint::point point_3)
        {
            ToolPaint::point new_point = {0, 0};

            if (type_ == CATMULL_ROM)
            {
                float coeff_0 = -t * pow(1.f - t, 2.f);
                float coeff_1 = (2.f - 5.f*pow(t, 2) + 3.f*pow(t, 3));
                float coeff_2 = t * (1.f + 4.f*t - 3.f*pow(t, 2));
                float coeff_3 = pow(t, 2) * (1.f - t);

                new_point.x = 0.5 * (coeff_0 * point_0.x + coeff_1 * point_1.x + coeff_2 * point_2.x - coeff_3 * point_3.x);
                new_point.y = 0.5 * (coeff_0 * point_0.y + coeff_1 * point_1.y + coeff_2 * point_2.y - coeff_3 * point_3.y);
            }

            return new_point;
        }
    };
    
    std::deque<point> points_;
    Interpolator interpolator_;
    uint32_t color_ = (1 << 16) - 1;
    uint32_t width_ = 1;
    HSVwindow hsv_window_;

    ToolPaint() : Tool(),
        interpolator_(CATMULL_ROM),
        hsv_window_(Vector2d(200, 400), Vector2d(110, 600))
    {
        char icon_path[128] = "source/paint-brush.png";
        std::memcpy(icon_path_, icon_path, 128);
        
        buildSetupWidget();
    }
    
    void paint(booba::Image *image)
    {
        float x = points_.back().x;
        float y = points_.back().y;

        image->putPixel(x, y, color_);

        if (points_.size() == 4)
        {
            for (float t = 0; t <= 1.f; t += 0.001)
            {
                point new_point = interpolator_(t, points_[0], points_[1], points_[2], points_[3]);
                image->putPixel(new_point.x, new_point.y, color_);
            }
        }
    }

    void apply(booba::Image* image, const booba::Event* event) override
    {    
        switch (event->type)
        {
            case booba::EventType::MouseMoved:
            {
                point new_point = {(float)event->Oleg.motion.x, (float)event->Oleg.motion.y};

                if (points_.size() > 0)
                {
                    if (abs(points_.back().x - new_point.x) > image->getX() / 100 + 1 || abs(points_.back().y - new_point.y) > image->getH() / 10 + 1)
                    {
                        points_.clear();
                    }
                }

                points_.push_back(new_point);
                
                if (points_.size() > 4)
                {
                    points_.pop_front();
                }

                paint(image);

                break;
            }

            case booba::EventType::ButtonClicked:
            {
                if (event->Oleg.bcedata.id == tool_button_)
                {
                    std::cout << "Brush " << is_on_ << std::endl;
 
                    ToolManager &tool_manager = ToolManager::getInstance();
                    
                    if (!is_on_)
                    {
                        tool_manager.set_active_tool(this);
                    }
                    
                    else
                    {
                        tool_manager.remove_active_tool();                        
                    }

                    is_on_ = !is_on_;
                }
            }
            
            default:
                break;
        }
    }

    const char* getTexture() override
    {
        return icon_path_;
    } 

    void buildSetupWidget()
    {
        tool_button_ = booba::createButton(25, 25, 50, 50, (char *)this);   
    }
};