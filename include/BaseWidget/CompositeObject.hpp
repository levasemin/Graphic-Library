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

        void add(Widget *widget) override;
        void remove(Widget *widget) override;
    
    protected:
        void draw() override;

        std::vector<Widget *> getChildren() const override;
        void setChildren(std::vector<Widget *> children) override;

        void moveMouseEvent      (const Event &event) override;

        void clickLeftEvent      (const Event &event) override;
        void releaseLeftEvent    (const Event &event) override;

        void clickRightEvent     (const Event &event) override;
        void releaseRightEvent   (const Event &event) override;
        
        void scrollEvent         (const Event &event) override;

        void pressKeyEvent       (const Event &event) override;

        void textEvent           (const Event &event) override;
    
    private:
        std::vector<Widget *> children_;
    };
}