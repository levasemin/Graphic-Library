#pragma GCC diagnostic ignored "-Wunused-parameter"

#pragma once

#include "../Application/Window.hpp"
#include "../Rendering/Rendering.hpp"
#include "../Classes/Vector2d.hpp"
#include "../BaseWidget/Widget.hpp"

namespace SL
{
    class Object : public Widget
    {
    public:
        Object(Vector2d shape, Vector2d position, const Texture &texture = Texture(Color::White));

        Object (const Object& source)  = default;
        Object &operator= (const Object& source)  = default;
        ~Object () override = default;
        
        void clickLeftEvent     (const Event &event) override;
        void releaseLeftEvent   (const Event &event) override;             

        void clickRightEvent    (const Event &event) override;
        void releaseRightEvent  (const Event &event) override;              
        
        void moveMouseEvent     (const Event &event) override;

        void pressKeyEvent      (const Event &event) override;
        void textEvent          (const Event &event) override;
        void scrollEvent        (const Event &event) override;

        bool pointBelong(Vector2d point) const override;

        void draw() override;

        void remove(Widget *window) override;

        void add(Widget *window) override;

        void display(Window *window) override;

        Vector2d getShape() const override;
        void setShape (Vector2d shape) override;

        Vector2d getPosition() const override;
        void setPosition(Vector2d position) override;

        std::pair<Vector2d, Vector2d> getField() const override;

        Vector2d getGlobalShape() const override;        

        Vector2d getVirtualShape() const override;
        
        Widget  *getParent() const override;
        void setParent(Widget *parent) override;

        Texture getTexture() const override;
        void setTexture(const Texture &texture) override;

        RenderTexture *getRenderTexture() override;
        void setRenderTexture(RenderTexture render_texture) override;

        std::vector<Widget *> getChildren() const override;
        void setChildren(std::vector<Widget *> children) override;

    protected:
        Vector2d shape_;
        Vector2d position_;
        Texture texture_;
        Sprite sprite_;

        Vector2d real_position_;
        
        RenderTexture render_texture_;
        Widget *parent_ = nullptr;

    };
}