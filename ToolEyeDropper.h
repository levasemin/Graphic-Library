#pragma once

#include <deque>

#include "Command.h"
#include "Color.h"
#include "Circle.h"
#include "tools.h"
#include "Label.h"
#include "Interpolator.h"

class ToolEyeDropper : booba::Tool
{
private:
    Color color_;

    Label color_box_label_;
    Label label_r_;
    Label label_g_;
    Label label_b_;

    uint64_t color_box_canvas_ = (uint64_t)nullptr;
    uint64_t canvas_r_         = (uint64_t)nullptr;
    uint64_t canvas_g_         = (uint64_t)nullptr;
    uint64_t canvas_b_         = (uint64_t)nullptr;

    bool clicked_ = false;
    
    char icon_path_[128] = "source/EyeDropper.png";

public:
    ToolEyeDropper():
        color_(uint8_t(0), uint8_t(0), uint8_t(0)),
        color_box_label_(Vector2d(100, 100), Vector2d(110, 110)),
        label_r_  (Vector2d(50, 50), Vector2d(195, 35)),
        label_g_  (Vector2d(50, 50), Vector2d(195, 95)),
        label_b_  (Vector2d(50, 50), Vector2d(195, 155))
    {
        label_r_.set_texture(Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
        label_g_.set_texture(Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
        label_b_.set_texture(Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
        
        label_r_.set_color_text(Color(uint8_t(190), uint8_t(190), uint8_t(190)));
        label_g_.set_color_text(Color(uint8_t(190), uint8_t(190), uint8_t(190)));
        label_b_.set_color_text(Color(uint8_t(190), uint8_t(190), uint8_t(190)));

        booba::addTool(this);
        buildSetupWidget();
    }

    ToolEyeDropper           (const ToolEyeDropper &) = default;
    ToolEyeDropper &operator=(const ToolEyeDropper &) = default;

    void set_color(const Color &color)
    {
        color_ = color;

        color_box_label_.set_texture(Texture(color));

        fill_canvas(color_box_canvas_, color_box_label_);

        label_r_.setString(std::to_string(int(color.get_r())));
        label_g_.setString(std::to_string(int(color.get_g())));
        label_b_.setString(std::to_string(int(color.get_b())));
        
        fill_canvas(canvas_r_, label_r_);
        fill_canvas(canvas_g_, label_g_);
        fill_canvas(canvas_b_, label_b_);
    }
    
    void fill_canvas(uint64_t canvas, Label &label)
    {
        Image image(label.get_render_texture()->getTexture());   

        for (int y = 0; y < int(label.get_shape().y_); y++)
        {
            for (int x = 0; x < int(label.get_shape().x_); x++)
            {
                booba::putPixel(canvas, x, int(label.get_shape().y_) - y, image.getPixel(x, y));
            }
        }
    }

    const char* getTexture() override
    {
        return icon_path_;
    } 

    void apply(booba::Image* image, const booba::Event* event) override;

    void buildSetupWidget() override
    {
        color_box_canvas_ = booba::createCanvas(110, 110, 100, 100);
        canvas_r_         = booba::createCanvas(195, 35, 50, 50);
        canvas_g_         = booba::createCanvas(195, 95, 50, 50);
        canvas_b_         = booba::createCanvas(195, 180, 50, 50);
    }

    ~ToolEyeDropper()
    {}
};