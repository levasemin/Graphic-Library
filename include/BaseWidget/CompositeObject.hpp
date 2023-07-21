#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "Object.hpp"
#include "Widget.hpp"

namespace SL
{
    class CompositeObject : public Object
    {
    public:
        CompositeObject(Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::White));

        CompositeObject(const CompositeObject &source) = default;
        CompositeObject &operator=(const CompositeObject &source) = default;
        ~CompositeObject() = default;

        void clickLeftEvent      (const Event &event) override;
        void releaseLeftEvent    (const Event &event) override;

        void clickRightEvent     (const Event &event) override;
        void releaseRightEvent   (const Event &event) override;
        
        void moveMouseEvent      (const Event &event) override;

        void pressKeyEvent       (const Event &event) override;
        void textEvent           (const Event &event) override;
        void scrollEvent         (const Event &event) override;

        void draw() override;
        
        void remove(Widget *widget);

        void add(Widget *widget);
        
        std::vector<Widget *> getChildren() const override;
        void setChildren(std::vector<Widget *> children) override;
    
    protected:
        std::vector<Widget *> children_;
    };
}