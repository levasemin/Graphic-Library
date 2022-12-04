#pragma once

#include <deque>

#include "Command.h"
#include "Color.h"
#include "Circle.h"
#include "tools.h"
#include "Interpolator.h"

class ToolEraser : public booba::Tool
{

public:

    bool clicked_ = false;
    char icon_path_[128] = "source/Eraser.png";

    Interpolator interpolator_;
    uint64_t width_scroll_bar_   = (uint64_t)nullptr;
    uint64_t settings_container_ = (uint64_t)nullptr;

    std::deque<Vector2d> points_;

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