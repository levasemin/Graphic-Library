#pragma once

#include "Tool.h"
#include "Command.h"
#include "ToolCommand.h"
#include "ToolManager.h"
#include "Color.h"
#include "Circle.h"
#include "HorizontalScrollBar.h"
#include "HSVwindow.h"
#include <deque>

class SuperToolPaint : public Tool
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
        
        static const int CATMULL_ROM = 0;

        SuperToolPaint::point operator()(float t, SuperToolPaint::point point_0, SuperToolPaint::point point_1, SuperToolPaint::point point_2, SuperToolPaint::point point_3)
        {
            SuperToolPaint::point new_point = {0.f, 0.f};

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
    HSVwindow hsv_window_;
    HorizontalScrollBar width_scroll_bar_;

    std::deque<point> points_;

    Circle drawing_object_;

    bool clicked_ = false;

    SuperToolPaint() : Tool(),
        interpolator_(Interpolator::CATMULL_ROM),
        hsv_window_(Vector2d(200, 300), Vector2d(150, 250)),
        width_scroll_bar_(Vector2d(200, 30), Vector2d(150, 40)),
        points_({}),
        drawing_object_(1.f)
    {
        hsv_window_.set_command(             (Command<const Color &> *) new SimpleCommand<SuperToolPaint, const Color &>(this, &SuperToolPaint::set_color));
        width_scroll_bar_.set_scroll_command((Command<const Event &> *) new SimpleCommand<SuperToolPaint, const Event &>(this, &SuperToolPaint::set_width));
                
        char icon_path[128] = "source/Brush.png";
        std::memcpy(icon_path_, icon_path, 128);
        booba::addTool(this);
        
        buildSetupWidget();
    }

    SuperToolPaint(const SuperToolPaint &) = default;
    SuperToolPaint &operator=(const SuperToolPaint &) = default;

    void set_color(const Color &color)
    {
        drawing_object_.set_color(color);
    }

    void set_width(const Event & event)
    {
        drawing_object_.set_radius(int(event.Oleg_.smedata.value * 30.f));
    }

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
        case booba::EventType::CanvasMPressed:
        {
            clicked_ = true;

            point new_point = {(float)event->Oleg.motion.x, (float)event->Oleg.motion.y};

            points_.push_back(new_point);
            paint(image);
            points_.pop_back();

            break;
        }

        case booba::EventType::CanvasMReleased:
        {
            clicked_ = false;
            break;
        }

        case booba::EventType::CanvasMMoved:
        {
            if (clicked_)
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
            }
            
            break;
        }

        case booba::EventType::ButtonClicked:

        case booba::EventType::ScrollbarMoved:

        case booba::EventType::NoEvent:
        case booba::EventType::MouseMoved:
        {
            clicked_ = false;
            break;
        }
        case booba::EventType::MousePressed:
        case booba::EventType::MouseReleased:
        {
            clicked_ = false;
            break;
        }
        
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
        ToolManager &tool_manager = ToolManager::getInstance();

        tool_manager.setting_palettes_.back()->add(&width_scroll_bar_);
        tool_manager.setting_palettes_.back()->add(&hsv_window_);
        hsv_window_.set_texture(tool_manager.get_setting_field()->get_texture());
    }
};