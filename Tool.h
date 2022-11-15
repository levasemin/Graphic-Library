#include "Widget.h"

class Tool
{
private:
    
public:
    Tool();
    ~Tool();

    virtual void apply(Widget *widget) = 0;
};
