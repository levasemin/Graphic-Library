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
        
        void clickLeftEvent      (const Event &event) override;
        void releaseLeftEvent   (const Event &event) override;             

        void clickRightEvent     (const Event &event) override;
        void releaseRightEvent  (const Event &event) override;              
        
        void moveMouseEvent      (const Event &event) override;

        void pressKeyEvent       (const Event &event) override;
        void textEvent           (const Event &event) override;
        void scrollEvent         (const Event &event) override;

        bool pointBelong(Vector2d point) const override;

        void draw() override;

        void remove(Widget *window) override;

        void add(Widget *window) override;

        void display(Window *window) override;

        Vector2d getPosition() const override;
        void setPosition(Vector2d position) override;

        Vector2d getShape() const override;
        void setShape (Vector2d shape) override;

        Widget  *getParent() const override;
        void setParent(Widget *parent) override;

        Texture getTexture() const override;
        void setTexture(const Texture &texture) override;

        RenderTexture *getRenderTexture() override;
        void setRenderTexture(RenderTexture render_texture) override;

        Vector2d getGlobalShape() const override;

        Vector2d getGlobalOffset() const override; 
        void setGlobalOffset(Vector2d offset) override;

        Vector2d getLocalOffset() const override;
        void setLocalOffset(Vector2d diff_offset) override;
        
        bool getHasLocalOffset () const override;
        void setHasLocalOffset(bool has) override;
        
        Vector2d getStartField() const override;
        Vector2d getEndField() const override;

        std::vector<Widget *> getChildren() const override;
        void setChildren(std::vector<Widget *> children) override;
    };
}