#pragma once

#include "../BaseWidget/BaseWidget.hpp"

namespace SL
{
    class Decorator : public Widget
    {

    protected: 
        Widget *widget_ = nullptr;

    public:

        Decorator (Widget *widget);

        Decorator(const Decorator &source) = default;
        Decorator &operator=(const Decorator &source) = default;
        Decorator(Decorator &&source) = default;
        Decorator &operator=(Decorator &&source) = default;
        virtual ~Decorator() = default;

        void ClickLeftEvent      (const Event &event) override;
        void ReleasedLeftEvent   (const Event &event) override;

        void ClickRightEvent (const Event &event) override;
        void ReleasedRightEvent (const Event &event) override;

        void MoveMouseEvent (const Event &event) override;

        void PressKeyEvent (const Event &event) override;

        void TextEvent (const Event &event) override;
        
        void ScrollEvent (const Event &event) override;
        

        bool point_belonging(Vector2d point) const override;

        void draw() override;
        
        void remove(Widget *window) override;

        void add(Widget *window) override;

        void display(Window *window) override;


        Vector2d get_position() const override;
        void set_position(Vector2d position) override;

        Vector2d get_shape() const override;
        void set_shape(Vector2d shape) override;

        Widget *get_parent() const override;
        void set_parent(Widget *parent) override;

        virtual Texture get_texture() const override;
        virtual void set_texture(const Texture &texture) override;

        RenderTexture *get_render_texture() override;
        void set_render_texture(RenderTexture render_texture) override;

        Vector2d get_indent() const override;
        void set_indent(Vector2d indent) override;

        Vector2d get_global_shape() const override;
        void set_global_offset(Vector2d offset) override;

        Vector2d get_global_offset() const override;
        void set_global_shape(Vector2d global_shape) override;
    
        Vector2d get_local_offset() const override;
        void set_local_offset(Vector2d offset) override;

        bool get_has_local_offset() const override;
        void set_has_local_offset(bool has) override;

        Vector2d get_start_field() const override;
        Vector2d get_end_field() const override;

        std::vector<Widget *> get_children() const override;
        void set_children(std::vector<Widget *> children) override;
    };
}