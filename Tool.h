#include "Decorator.h"
#include "Widget.h"

class DecoratorPaint : public Decorator
{
public:
    Color color_;

    DecoratorPaint (Widget *widget, Color color) : 
        color_(color),
        Decorator(widget)
    {
    }

    void ClickLeftEvent(Vector2d point)
    {
        if (point_belonging(point))
        {
            sf:: sp;
            sp.        
        }
    }
};