#include "Vector2d.h"
#include "VirtualWindow.h"
#include <string>

class Label: VirtualWindow
{

public:

    std::string text_;

    Label(Vector2d shape, Vector2d center, Texture texture, const char *text): VirtualWindow(shape, center, texture),
        text_(text)
    {

    }

    void draw() override
    {
        VirtualWindow::draw();
        
    }
};