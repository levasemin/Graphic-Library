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

        void ClickLeftEvent      (const Event &event) override;
        void ReleasedLeftEvent    (const Event &event) override;

        void ClickRightEvent     (const Event &event) override;
        void ReleasedRightEvent  (const Event &event) override;
        
        void MoveMouseEvent      (const Event &event) override;
        
        void TextEvent           (const Event &event) override;

        void PressKeyEvent       (const Event &event) override;
        
        void ScrollEvent         (const Event &event) override;

        void set_global_offset(Vector2d offset) override;

        void draw() override;
        
        void reset_global_shape();

        void remove(Widget *widget);

        void add(Widget *widget);
        
        std::vector<Widget *> get_children() const override;
        void set_children(std::vector<Widget *> children) override;

        Vector2d get_indent() const override;
        void set_indent(Vector2d indent) override;

        Vector2d get_global_shape() const override;
        void set_global_shape(Vector2d global_shape) override;

        Vector2d get_local_offset() const;
        void set_local_offset(Vector2d offset);
    };
}