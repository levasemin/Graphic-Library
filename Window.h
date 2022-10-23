#include "Widget.h"
#include "Event.h"

template <class ...TParams>
class Window: public Widget
{
public:
    Window(int w, int h, int style) : Widget(w, h, style) {};
    Event<TParams ...> onButtonClick;
};


class ClickWindowHandler
{
public:
    void print_int(char *text)
    {
        std::cout << text << std::endl;
    }

    void print_long_long (char * text)
    {
        std::cout << text << "123";
    }
};