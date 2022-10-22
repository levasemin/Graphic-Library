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
    void operator ()(long long text)
    {
        std::cout << text << std::endl;
    }

    void operator ()(int text)
    {
        std::cout << text << "123";
    }
};