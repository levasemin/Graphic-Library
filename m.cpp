#include "GraphicLib.h"

int main()
{
    MainWindow window(Vector2d(500, 500), Texture(Colors::Blue));
    Font font("/home/levce/projectsDED/event_handler2/Event_handler/fonts/ofont.ru_Times New Roman.ttf");
    Text text(font);
    text.setString("Hello");
    text.setFillColor(Colors::Green);
    Button butt(Vector2d(100, 100), Vector2d(300, 300), Texture(Colors::Yellow));
    butt.set_text(text);
    window.add(&butt);
    
    Application app(&window);
    app.exec();
}   