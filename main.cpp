#include "GraphicLib.h"
#include "SaveWindow.h"
#include "OpenWindow.h"

#include <iostream>
#include <vector>
#include <string>

const std::string path_mountain = "/home/levce/projectsDED/event_handler2/Event_handler/source/british.jpg";

SaveWindow create_save_window()
{
    Button *save_button = new Button(Vector2d(60, 30), Vector2d(70, 215), Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
    save_button->setString("Save");
    
    Editor *path_editor = new Editor(Vector2d(200, 50), Vector2d(150, 125));
    path_editor->setTextColor(Color(uint8_t(190), uint8_t(190), uint8_t(190)));
    path_editor->set_texture(Texture(Color(uint(31), uint8_t(31), uint8_t(31))));
    path_editor->setAlignment(Label::Alignment::LeftCenter);
    
    Button *cancel_button = new Button(Vector2d(60, 30), Vector2d(150, 215), Texture(Color::Grey));
    cancel_button->setString("Cancel");

    SaveWindow save_window(Vector2d(400, 300), save_button, cancel_button, path_editor);

    return save_window;
}

OpenWindow create_open_window()
{
    Button *open_button = new Button(Vector2d(60, 30), Vector2d(70, 215), Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
    open_button->setString("Open");
    
    Editor *path_editor = new Editor(Vector2d(200, 50), Vector2d(150, 125));
    path_editor->setTextColor(Color(uint8_t(190), uint8_t(190), uint8_t(190)));
    path_editor->set_texture(Texture(Color(uint(31), uint8_t(31), uint8_t(31))));
    path_editor->set_texture(Texture(Color(uint(31), uint8_t(31), uint8_t(31))));
    path_editor->setAlignment(Label::Alignment::LeftCenter);

    Button *cancel_button = new Button(Vector2d(60, 30), Vector2d(150, 215), Texture(Color::Grey));
    cancel_button->setString("Cancel");

    OpenWindow open_window(Vector2d(400, 300), open_button, cancel_button, path_editor);

    return open_window;
}

// struct HSV
// {
//     double h;
//     double s;
//     double v; 
// };

// HSV ConvertRGBToHSV(const uint32_t rgb) {
//     double r = ((rgb & (0xFF << 24u)) >> 24u) / 255.0;
//     double g = ((rgb & (0xFF << 16u)) >> 16u) / 255.0;
//     double b = ((rgb & (0xFF << 8u))  >> 8u) / 255.0;

//     double cmax = std::max(r, std::max(g, b)); // maximum of r, g, b
//     double cmin = std::min(r, std::min(g, b)); // minimum of r, g, b
//     double diff = cmax - cmin; // diff of cmax and cmin.
//     double h = -1, s = -1;
 
//     // if cmax and cmax are equal then h = 0
//     if (cmax == cmin)
//         h = 0;
 
//     // if cmax equal r then compute h
//     else if (cmax == r)
//         h = fmod(60 * ((g - b) / diff) + 360, 360);
 
//     // if cmax equal g then compute h
//     else if (cmax == g)
//         h = fmod(60 * ((b - r) / diff) + 120, 360);
 
//     // if cmax equal b then compute h
//     else if (cmax == b)
//         h = fmod(60 * ((r - g) / diff) + 240, 360);
 
//     // if cmax equal zero
//     if (cmax == 0)
//         s = 0;
//     else
//         s = (diff / cmax) * 100;
 
//     // compute v
//     double v = cmax * 100;
//     return {h, s, v};
// }

booba::ApplicationContext* booba::APPCONTEXT = nullptr;

int main()
{   
    // Color color(uint8_t(255), 255, 255);       
    // uint32_t uint_color = Color::convert_color_uint(color);
    // HSV hsv = ConvertRGBToHSV(uint_color);
    // std::cout << hsv.h << " " << hsv.s << " " << hsv.v;

    booba::APPCONTEXT = new booba::ApplicationContext();
    booba::APPCONTEXT->fgColor = 0xFF000000;
    booba::APPCONTEXT->bgColor = 0xFF000000;
    
    MainWindow main_window(Vector2d(WIDTH, HEIGHT), Texture(Color::Grey));

    TextureManager &texture_manager = TextureManager::getInstance();
    texture_manager.load_textures("Textures");

    Image image(path_mountain);
    ToolPalette tool_palette(Vector2d(300, 300), Vector2d(160, 173), Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
    Container setting_container(Vector2d(300, 588), Vector2d(160, 700));
    setting_container.set_texture(Texture(Color((uint8_t)48, (uint8_t)48, (uint8_t)48)));
    
    Canvas canvas(Vector2d(1400, 970), Vector2d(1020, 508), &tool_palette, &setting_container);

    canvas.set_image(image);
    
    SuperToolPaint super_tool_paint;

    DecoratorScrollBar scroll_bar_canvas(&canvas);
    
    ComboBox file_button(Vector2d(60, 20), Vector2d(30, 10), Texture(Color(uint8_t(48), uint8_t(48), uint8_t(48))));
    file_button.setString("File");
    file_button.setCharacterSize(16);
    file_button.set_box_texture(Texture(Color::Grey));


    Button file_save_button(Vector2d(50, 30), Vector2d(25, 15), Texture(Color::Grey));

    file_save_button.setCharacterSize(16);
    file_save_button.setString("Save");
    file_save_button.setTextColor(Color(uint8_t(190), uint8_t(190), uint8_t(190)));

    SaveWindow save_window = create_save_window();
    save_window.set_canvas(&canvas);
    file_save_button.set_left_click((Command<const Event &> *) new SimpleCommand<SaveWindow, const Event &>(&save_window, &SaveWindow::exec));


    Button file_open_button(Vector2d(50, 30), Vector2d(25, 45), Texture(Color::Grey));
    
    file_open_button.setCharacterSize(16);
    file_open_button.setString("Open");
    file_open_button.setTextColor(Color(uint8_t(190), uint8_t(190), uint8_t(190)));

    OpenWindow open_window = create_open_window();
    open_window.set_canvas(&canvas);
    file_open_button.set_left_click((Command<const Event &> *) new SimpleCommand<OpenWindow, const Event &>(&open_window, &OpenWindow::exec));


    file_button.add(&file_save_button);
    file_button.add(&file_open_button);

    main_window.add(&scroll_bar_canvas);    
    main_window.add(&tool_palette);
    main_window.add(&setting_container);
    main_window.add(&file_button);

    Editor edit(Vector2d(100, 20), Vector2d(300, 300));
    
    Application app(&main_window);
    
    app.exec();
}