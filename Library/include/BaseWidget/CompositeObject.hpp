#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "Object.hpp"
#include "Widget.hpp"

namespace SL
{
    class CompositeObject : public Object
    {

    protected:
        Vector2d global_shape_;

    public:
        std::vector<Widget *> children_;

        Vector2d indent_; 

        CompositeObject(Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::Red));

        CompositeObject(const CompositeObject &source);

        CompositeObject &operator=(const CompositeObject &source);

        void clickLeftEvent      (const Event &event) override;
        void releaseLeftEvent    (const Event &event) override;

        void clickRightEvent     (const Event &event) override;
        void releaseRightEvent   (const Event &event) override;
        
        void moveMouseEvent      (const Event &event) override;
        
        void textEvent           (const Event &event) override;

        void pressKeyEvent       (const Event &event) override;
        
        void scrollEvent         (const Event &event) override;

        void setGlobalOffset(Vector2d offset) override;

        void draw() override;
        
        void remove(Widget *widget);

        void add(Widget *widget);
        
        std::vector<Widget *> getChildren() const override;
        void setChildren(std::vector<Widget *> children) override;

        Vector2d getGlobalShape() const override;

        Vector2d getLocalOffset() const;
        void setLocalOffset(Vector2d offset);
    };
}