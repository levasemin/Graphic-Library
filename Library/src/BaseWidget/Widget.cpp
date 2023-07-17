#include "Widget.hpp"

namespace SL
{
    Widget &Widget::operator=(const Widget &&widget) 
    {
        return *this = widget;
    }
}