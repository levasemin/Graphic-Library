#pragma once

#include "Object.hpp"
#include "Widget.hpp"

namespace SL
{
    /**
     * @brief class CompositeObject is class of widget, that will have children.
     * @details class defines base logics of working every widget, it defines all methods as it will have children. 
     */
    class CompositeObject : public Object
    {
    public:
        /**
         * @brief Construct a new Composite Object object
         * 
         * @param shape 
         * @param position 
         * @param texture 
         */
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

        void pressEvent          (const Event &event) override;
        void releaseEvent        (const Event &event) override;
        
        void scrollEvent         (const Event &event) override;

        void pressKeyEvent       (const Event &event) override;

        void textEvent           (const Event &event) override;
        
        void resizedEvent        (const Event &event) override;
        
    private:
        std::vector<Widget *> children_; ///< vector of pointers on children
    };
}