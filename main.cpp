#include "GraphicLib.h"

#include <iostream>
#include <vector>


const char *path_british = "/home/levce/projectsDED/event_handler2/Event_handler/source/grid.jpg";

int main()
{          
    MainWindow main_window(Vector2d(1920, 1080), Texture(Colors::Blue));

    ComboBox combobox(Vector2d(80, 20), Vector2d(400, 100), Texture(Colors::Yellow));
    Button butt(Vector2d(50, 50), Vector2d(25, 25), Texture(Colors::Green));
    combobox.item_box_.add(&butt);

    Image image(path_british);
    // ToolPalette tool_palette(Vector2d(0, 0), Vector2d(600, 200), Texture(Colors::Magenta));
    // Canvas canvas(image.getSize(), image.getSize() / 2 + Vector2d(50, 50), image, &tool_palette);
    // ToolPaint toolpaint;
    // toolpaint.buildSetupWidget();
    
    // canvas.get_global_shape().print_value();

    // canvas.add_tool(&toolpaint);
    // DecoratorScroll scroll_canvas(&canvas);

    // main_window.add(&scroll_canvas);    
    // main_window.add(&tool_palette);
    // main_window.add(&combobox);

    // Application app(&main_window);

    // app.exec();
}