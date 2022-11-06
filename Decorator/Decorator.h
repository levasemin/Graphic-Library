#include "CompositeWidget.h"

class Decorator : public Widget
{
public:
    Decorator (Widget *widget): Widget(*widget)
    {
    }

    virtual void draw();

private:
};

void Decorator::draw()
{
    Widget::draw();
}