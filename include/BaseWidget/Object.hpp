#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "Window.hpp"
#include "Vector2d.hpp"
#include "Widget.hpp"

namespace SL
{
    class Object : public Widget
    {
    public:
        Object(Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::White));

        Object (const Object& source)  = default;
        Object &operator= (const Object& source)  = default;
        ~Object () override = default;
        
        void add(Widget *window) override;
        void remove(Widget *window) override;

        Vector2d getShape() const override;
        void setShape (Vector2d shape) override;

        Vector2d getPosition() const override;
        void setPosition(Vector2d position) override;

        Texture getTexture() const override;
        void setTexture(const Texture &texture) override;

        Color getColor() const override;
        void setColor(Color color) override;

    protected:
        void draw() override;
        void display(Window *window) override;

        Widget  *getParent() const override;
        void setParent(Widget *parent) override;
        
        std::vector<Widget *> getChildren() const override;
        void setChildren(std::vector<Widget *> children) override;

        RenderTexture *getRenderTexture() override;
        void setRenderTexture(RenderTexture render_texture) override;

        std::pair<Vector2d, Vector2d> getField() const override;

        bool pointBelong(Vector2d point) const override;

        void moveMouseEvent     (const Event &event) override;

        void clickLeftEvent     (const Event &event) override;
        void releaseLeftEvent   (const Event &event) override;             

        void clickRightEvent    (const Event &event) override;
        void releaseRightEvent  (const Event &event) override;              

        void scrollEvent        (const Event &event) override;
 
        void pressKeyEvent      (const Event &event) override;
        
        void textEvent          (const Event &event) override;
    
    private:
        Vector2d shape_;
        Vector2d position_;
        Texture texture_;
        Sprite sprite_;
        
        RenderTexture render_texture_;
        Widget *parent_ = nullptr;

        Vector2d max_start_;
        Vector2d max_end_;
        
        Vector2d getFieldLimits(const Widget *current, std::pair<Vector2d, Vector2d> *curr_limit) const;

        friend class CompositeObject;
    };
}