#pragma once

#include "Window.hpp"
#include "Widget.hpp"
#include "Vector2d.hpp"

namespace SL
{
    /**
     * @brief class Object is class of single widget, that won't never have a child.
     * @details class defines base logics of working every widget, it defines all methods as it won't never have a child. 
     */
    class Object : public Widget
    {
    public:
        /**
         * @brief Construct a new Object
         * 
         * @param shape 
         * @param position 
         * @param texture 
         */
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

        RenderTexture *getRenderTexture() override;

        std::pair<Vector2d, Vector2d> getField() const override;

        bool pointBelong(Vector2d point) const override;

        void moveMouseEvent     (const Event &event) override;

        void pressEvent     (const Event &event) override;
        void releaseEvent   (const Event &event) override;             

        void scrollEvent        (const Event &event) override;
 
        void pressKeyEvent      (const Event &event) override;
        
        void textEvent          (const Event &event) override;

        void resizedEvent       (const Event &event) override;
    private:
        Vector2d shape_;
        Vector2d position_;
        Texture  texture_;
        
        Sprite  sprite_;
        RenderTexture render_texture_;

        Widget *parent_ = nullptr;
        
        /**
         * @brief Get the Field Limits object
         * @details calculating left and right corners of object
         * @param current 
         * @param curr_limit 
         * @return Vector2d 
         */
        Vector2d getFieldLimits(const Widget *current, std::pair<Vector2d, Vector2d> *curr_limit) const;

        friend class CompositeObject;
    };
}