#include "MainWindow.hpp"

namespace SL
{
    MainWindow::MainWindow(Vector2d shape, Texture texture, int style):
            CompositeObject(shape, Vector2d(0, 0), texture),
            style_(style)
    {}
}