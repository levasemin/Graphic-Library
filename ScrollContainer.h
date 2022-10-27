#pragma once
#include "ScrollVirtualWindow.h"
#include "ScrollBar.h"
#include "Color.h"
#include "Vector2d.h"
#include <vector>

class ScrollContainer : public ScrollVirtualWindow
{
public:
    ScrollBar *scroll_bar_ = nullptr;

    ScrollContainer(Vector2d shape, Vector2d center, const Color &color = Colors::Red, VirtualWindow *parent = nullptr, std::vector<VirtualWindow *> children = {}) : 
        ScrollVirtualWindow(shape, center, color, parent, children)
    {
    };
    
    void set_scroll_bar(ScrollBar *new_scroll_bar)
    {
        if (scroll_bar_ != nullptr)
        {
            std::remove(children_.begin(), children_.end(), scroll_bar_);
        }

        scroll_bar_ = new_scroll_bar;
    
        add(scroll_bar_);
    }
    
    void set_offset(Vector2d offset) override
    {
        for (int i = 0; i < children_.size(); i++)
        {
            if (children_[i] == scroll_bar_)
            {
                continue;
            }
            
            children_[i]->center_ += offset;

            children_[i]->set_offset(offset);
        }
    }
};