// #pragma once

#include "ToolManager.h"
#include "ToolButton.h"
#include "Label.h"
#include "ToolHorizontalScrollBar.h"
#include "Canvas.h"
#include "stdint.h"
#include "tools.h"


extern "C" uint64_t booba::createButton   (int32_t x, int32_t y, uint32_t w, uint32_t h, const char* text)
{   
    ToolManager &tool_manager = ToolManager::getInstance();

    ToolButton *tool_button = new ToolButton(Vector2d((float)w, (float)h), Vector2d((float)x, (float)y), Texture(tool_manager.init_tool_->getTexture()));

    tool_button->set_left_click((Command<const booba::Event &> *) new ToolCommand<booba::Tool>(tool_manager.init_tool_, &Tool::apply));
    
    tool_manager.setting_palettes_.back()->add(tool_button);

    return (int64_t)tool_button;
}

extern "C" uint64_t booba::createLabel    (int32_t x, int32_t y, uint32_t w, uint32_t h, const char* text)
{
    ToolManager &tool_manager = ToolManager::getInstance();

    Label *label = new Label(Vector2d(float(w), float(h)), Vector2d(float(x), float(y)));
    label->setString(text);

    tool_manager.setting_palettes_.back()->add(label);

    return (int64_t)label;    
}   

extern "C" uint64_t booba::createScrollbar(int32_t x, int32_t y, uint32_t w, uint32_t h)
{
    ToolManager &tool_manager = ToolManager::getInstance();

    ToolHorizontalScrollBar *scroll_bar = new ToolHorizontalScrollBar(Vector2d(float(w), float(h)), Vector2d(float(x), float(y)));

    scroll_bar->set_scroll_command((Command <const booba::Event &> *) new ToolCommand<booba::Tool>(tool_manager.init_tool_, &Tool::apply));

    tool_manager.setting_palettes_.back()->add(scroll_bar);

    return (int64_t)scroll_bar;     
}

extern "C" uint64_t booba::createCanvas(int32_t x, int32_t y, int32_t w, int32_t h)
{
    ToolManager &tool_manager = ToolManager::getInstance();

    Canvas *canvas = new Canvas(Vector2d(float(w), float(h)), Vector2d(float(x), float(y)));

    tool_manager.setting_palettes_.back()->add(canvas);

    return (int64_t)canvas;
}

extern "C" uint64_t booba::putPixel (uint64_t canvas, int32_t x, int32_t y, uint32_t color)
{
    if (canvas)
    {
        Canvas *my_canvas = (Canvas *)canvas;
        my_canvas->surface_->image_.putPixel(x, y, color);
    }

    return canvas;
}

extern "C" uint64_t booba::putSprite(uint64_t canvas, int32_t x, int32_t y, uint32_t w, uint32_t h, const char* texture)
{
    // if (canvas)
    // {
    //     Canvas *my_canvas = (Canvas *)canvas;
    //     my_canvas->surface_.   
    // }
    
    return canvas;
}

extern "C" void booba::addTool(booba::Tool* tool)
{
    ToolManager &tool_manager = ToolManager::getInstance();
    tool_manager.add(tool);  
}

extern "C" void booba::addFilter(booba::Tool* tool)
{

}