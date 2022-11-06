#include "Decorator/Decorator.h"
#include "ScrollBar.h"

class DecoratorScrollBar : public Decorator
{

public:
    DecoratorScrollBar(Widget *widget) : Decorator(widget),
        scroll_bar_(Vector2d(20, widget->shape_.y_), Vector2d(10, widget->shape_.y_ / 2), Texture(Colors::Blue))
    {
        
    }

    ScrollBar scroll_bar_;
    void draw() override
    {

    }
};