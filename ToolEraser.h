#pragma once

#include "Tool.h"
#include "Command.h"
#include "Color.h"
#include "Circle.h"
#include <deque>

class ToolEraser : public Tool
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
        char icon_path[128] = "source/eraser.png";
        std::memcpy(icon_path_, icon_path, 128);

        booba::addTool(this);
        buildSetupWidget();
    }

    ToolEraser(const ToolEraser &) = default;
    ToolEraser &operator=(const ToolEraser &) = default;

    void paint(booba::Image *image)
    {
        drawing_object_.draw_on_image(image, Vector2d(points_.back().x, points_.back().y));

        if (points_.size() == 4)
        {
            for (float t = 0; t <= 1.f; t += 0.1f)
            {
                point new_point = interpolator_(t, points_[0], points_[1], points_[2], points_[3]);
                
                drawing_object_.draw_on_image(image, Vector2d(new_point.x, new_point.y));
            }
        }
    }

    void apply(booba::Image* image, const booba::Event* event) override
    {    
        if (image == nullptr && event == nullptr)
        {
            return;
        }

        switch (event->type)
        {
            case booba::EventType::CanvasMMoved:
            {
                point new_point = {(float)event->Oleg.motion.x, (float)event->Oleg.motion.y};

                if (points_.size() > 0)
                {
                    if (abs(points_.back().x - new_point.x) > float(image->getX()) / 100.f + 1.f || abs(points_.back().y - new_point.y) > float(image->getH()) / 10.f + 1.f)
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

                break;
            }

            case booba::EventType::ScrollbarMoved:
            {
                if (width_scroll_bar_ == event->Oleg.smedata.id)
                {
                    drawing_object_.set_radius(int(event->Oleg.smedata.value * 100.f));
                }

                break;
            }

            case booba::EventType::NoEvent:
            case booba::EventType::MouseMoved:
            case booba::EventType::MousePressed:
            case booba::EventType::MouseReleased:
            case booba::EventType::CanvasMPressed:
            case booba::EventType::CanvasMReleased:
            
            default:
                break;
        }
    }

    const char* getTexture() override
    {
        return icon_path_;
    } 

    void buildSetupWidget() override
    {
        width_scroll_bar_ = (uint64_t)booba::createScrollbar(100, 100, 100, 30);
    }
};

void booba::init_module()
{
    ToolEraser *tool_eraser = new ToolEraser();
}