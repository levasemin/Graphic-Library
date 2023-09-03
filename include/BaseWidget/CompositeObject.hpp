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

        void moveMouseEvent      (const Event &event) override;

        void clickEvent      (const Event &event) override;
        void releaseEvent    (const Event &event) override;
        
        void scrollEvent         (const Event &event) override;

        void pressKeyEvent       (const Event &event) override;

        void textEvent           (const Event &event) override;
    
    private:
        std::vector<Widget *> children_;
    };
}