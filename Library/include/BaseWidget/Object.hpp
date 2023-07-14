#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "Window.hpp"
#include "Texture.hpp"
#include "RenderTexture.hpp"
#include "Sprite.hpp"
#include "Vector2d.hpp"
#include "Widget.hpp"

namespace SL
{
    class Object : public Widget
    {
        
    protected:
        Vector2d shape_;
        Vector2d position_;
        Texture texture_;
        Sprite sprite_;

        Vector2d local_offset_;
        Vector2d global_offset_;
        
        RenderTexture render_texture_;
        Widget *parent_ = nullptr;

        bool has_local_offset_ = true;

    public:
        Object(Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::White));

        Object(const Object& source);
        Object &operator=(const Object& source);
        ~Object () override = default;
        
        void ClickLeftEvent      (const Event &event) override;
        void ReleasedLeftEvent   (const Event &event) override;             

        void ClickRightEvent     (const Event &event) override;
        void ReleasedRightEvent  (const Event &event) override;              
        
        void MoveMouseEvent      (const Event &event) override;

        void PressKeyEvent       (const Event &event) override;
        void TextEvent           (const Event &event) override;
        void ScrollEvent         (const Event &event) override;

        bool point_belonging(Vector2d point) const override;

        void draw() override;

        void remove(Widget *window) override;

        void add(Widget *window) override;

        void display(Window *window) override;

        Vector2d get_position() const override;
        void set_position(Vector2d position) override;

        Vector2d get_shape() const override;
        void set_shape (Vector2d shape) override;

        Widget  *get_parent() const override;
        void set_parent(Widget *parent) override;

        Texture get_texture() const override;
        void set_texture(const Texture &texture) override;

        RenderTexture *get_render_texture() override;
        void set_render_texture(RenderTexture render_texture) override;

        Vector2d get_indent() const override;
        void set_indent(Vector2d indent) override;

        Vector2d get_global_shape() const override;
        void set_global_shape(Vector2d global_shape) override;

        Vector2d get_global_offset() const override; 
        void set_global_offset(Vector2d offset) override;

        Vector2d get_local_offset() const override;
        void set_local_offset(Vector2d diff_offset) override;
        
        bool get_has_local_offset () const override;
        void set_has_local_offset(bool has) override;
        
        Vector2d get_start_field() const override;
        Vector2d get_end_field() const override;

        std::vector<Widget *> get_children() const override;
        void set_children(std::vector<Widget *> children) override;
    };
}