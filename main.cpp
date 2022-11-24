#include "GraphicLib.h"

#include <iostream>
#include <vector>


const char *path_british = "/home/levce/projectsDED/event_handler2/Event_handler/source/british.jpg";

int main()
{          
    MainWindow main_window(Vector2d(WIDTH, HEIGHT), Texture(Colors::Blue));

    HSVpalette color_palette(Vector2d(200, 400), Vector2d(300, 300));
    // ComboBox combobox(Vector2d(80, 20), Vector2d(400, 100), Texture(Colors::Yellow));
    // Button butt(Vector2d(50, 50), Vector2d(25, 25), Texture(Colors::Green));
    // combobox.add(&butt);

    // Image image(path_british);
    // ToolPalette tool_palette(Vector2d(100, 300), Vector2d(600, 200), Texture(Colors::Magenta));
    // Canvas canvas(Vector2d(500, 500), Vector2d(300, 300), image, &tool_palette);
    
    // ToolPaint toolpaint;
    // toolpaint.buildSetupWidget();
    // canvas.add_tool(&toolpaint);
    // ToolEraser tooleraser;
    // tooleraser.buildSetupWidget();
    // canvas.add_tool(&tooleraser);
    
    // DecoratorScroll scroll_canvas(&canvas);

    // main_window.add(&scroll_canvas);    
    // main_window.add(&tool_palette);
    // main_window.add(&combobox);

    Application app(&main_window);
    main_window.add(&color_palette);
    app.exec();
}