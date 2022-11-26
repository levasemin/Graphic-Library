#include "GraphicLib.h"

#include <iostream>
#include <vector>


const char *path_british = "/home/levce/projectsDED/event_handler2/Event_handler/source/british.jpg";

int main()
{          
    MainWindow main_window(Vector2d(WIDTH, HEIGHT), Texture(Color::Blue));

    Image image(path_british);
    ToolPalette tool_palette(Vector2d(100, 300), Vector2d(60, 160), Texture(Color::Magenta));
    Canvas canvas(Vector2d(1400, 1000), Vector2d(820, 540), image, &tool_palette);


    ComboBox combobox(Vector2d(80, 20), Vector2d(40, 10), Texture(Color::Yellow));
    Button butt(Vector2d(50, 50), Vector2d(25, 25), Texture(Color::Green));
    combobox.add(&butt);

    
    
    ToolPaint toolpaint;
    toolpaint.buildSetupWidget();
    canvas.add_tool(&toolpaint);
    ToolEraser tooleraser;
    tooleraser.buildSetupWidget();
    canvas.add_tool(&tooleraser);
    
    DecoratorScroll scroll_canvas(&canvas);

    main_window.add(&scroll_canvas);    
    main_window.add(&tool_palette);
    main_window.add(&combobox);
    
    // Editor edit(Vector2d(100, 20), Vector2d(300, 300));
    
    // HSVwindow hsv_window(Vector2d(200, 400), Vector2d(200, 400) / 2);
    // Font font(TIMES_NEW_ROMAN_FONT);
    Application app(&main_window);
    
    app.exec();
}