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

        Decorator(const Decorator &source);
        Decorator &operator=(const Decorator &source);
        Decorator(Decorator &&source);
        Decorator &operator=(Decorator &&source);
        ~Decorator();

        void clickLeftEvent      (const Event &event) override;
        void releaseLeftEvent   (const Event &event) override;

        void clickRightEvent (const Event &event) override;
        void releaseRightEvent (const Event &event) override;

        void moveMouseEvent (const Event &event) override;

        void pressKeyEvent (const Event &event) override;

        void textEvent (const Event &event) override;
        
        void scrollEvent (const Event &event) override;
        

        bool pointBelong(Vector2d point) const override;

        void draw() override;
        
        void remove(Widget *window) override;

        void add(Widget *window) override;

        void display(Window *window) override;


        Vector2d getPosition() const override;
        void setPosition(Vector2d position) override;

        Vector2d getShape() const override;
        void setShape(Vector2d shape) override;

        Widget *getParent() const override;
        void setParent(Widget *parent) override;

        virtual Texture getTexture() const override;
        virtual void setTexture(const Texture &texture) override;

        RenderTexture *getRenderTexture() override;
        void setRenderTexture(RenderTexture render_texture) override;
        
        Vector2d getGlobalShape() const override;

        Vector2d getVirtualShape() const override;
        
        std::pair<Vector2d, Vector2d> getField() const override;

        std::vector<Widget *> getChildren() const override;
        void setChildren(std::vector<Widget *> children) override;
    };
}