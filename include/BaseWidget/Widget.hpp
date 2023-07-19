/**
 * @file Widget.hpp
 * @author Semin Lev (you@domain.com)
 * @brief declaration class Widget
 * @version 0.1
 * @date 2023-07-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include "../Application/Window.hpp"
#include "../Rendering/Rendering.hpp"
#include "../Classes/Vector2d.hpp"
#include "../Event/Event.hpp"

namespace SL
{
    /**
     * @brief Virtual class Widget, skeleton of every object.
     * @details Widget is parent of every library's object. It  has list of virtual functions, that must be defined in every class
     * for working in system of rendering and event spreading. 
     */
    class Widget
    {
    public:

        Widget() {}
        /**
         * @brief handle left mouse clicking
         * 
         * @param event 
         */
        virtual void clickLeftEvent      (const Event &event)          = 0;
        
        /**
         * @brief handle left mouse releasing
         * 
         * @param event 
         */
        virtual void releaseLeftEvent   (const Event &event)          = 0;              

        /**
         * @brief handle right mouse clicking
         * 
         * @param event 
         */
        virtual void clickRightEvent     (const Event &event)          = 0;
        
        /**
         * @brief handle right mouse releasing
         * 
         * @param event 
         */
        virtual void releaseRightEvent  (const Event &event)          = 0;              
        
        /**
         * @brief handle mouse moving
         * 
         * @param event 
         */
        virtual void moveMouseEvent      (const Event &event)          = 0;

        /**
         * @brief handle key pressing
         * 
         * @param event 
         */
        virtual void pressKeyEvent       (const Event &event)          = 0;
                    
        /**
         * @brief handle mouse scrolling
         * 
         * @param event 
         */
        virtual void scrollEvent         (const Event &event)          = 0;
        
        /**
         * @brief handle text entering
         * 
         * @param event 
         */
        virtual void textEvent           (const Event &event)          = 0;

        /**
         * @brief check belonging point to object
         * 
         * @param point 
         * @return true belonging
         * @return false not belonging
         */
        virtual bool pointBelong(Vector2d point) const             = 0;

        /**
         * @brief draw object on parent, if it exists
         * 
         */
        virtual void draw()                                            = 0; 

        /**
         * @brief add child widget
         * 
         * @param child 
         */
        virtual void add(Widget *child)                               = 0;

        /**
         * @brief remove child widget
         * 
         * @param child 
         */
        virtual void remove(Widget *child)                            = 0;

        /**
         * @brief Get the position object
         * 
         * @return Vector2d current position
         */
        virtual Vector2d getPosition() const                          = 0;
        /**
         * @brief Set the position object
         * 
         * @param position new position
         */
        virtual void setPosition(Vector2d position)                   = 0;
        
        /**
         * @brief get current shape of widget
         * 
         * @return Vector2d 
         */
        virtual Vector2d getShape() const                             = 0;
        /**
         * @brief Set new shape for widget
         * 
         * @param shape new shape
         */
        virtual void setShape(Vector2d shape)                         = 0;

        /**
         * @brief get pointer on parent of widget
         * 
         * @return Widget* 
         */
        virtual Widget *getParent() const                             = 0;
        /**
         * @brief set new parent for widget
         * 
         * @param parent 
         */
        virtual void setParent(Widget *parent)                        = 0;

        /**
         * @brief get Texture of widget
         * 
         * @return Texture 
         */
        virtual Texture getTexture() const                            = 0;
        /**
         * @brief set new Texture for widget 
         * 
         * @param texture new Texture
         */
        virtual void setTexture(const Texture &texture)               = 0;

        /**
         * @brief Get the Children object
         * 
         * @return std::vector<Widget *> 
         */
        virtual std::vector<Widget *> getChildren() const             = 0;
        /**
         * @brief Set the Children object
         * 
         * @param children 
         */
        virtual void setChildren(std::vector<Widget *> children)      = 0;

        /**
         * @brief 
         * 
         * @param widget 
         * @return Widget& 
         */
        virtual Widget &operator=(const Widget &widget) = default;
        virtual ~Widget() = default;

        /**
         * @brief display all drawing changes on object
         * 
         * @param window 
         */
        virtual void display(Window *window)                           = 0;

        /**
         * @brief get pointer on current RenderTexture
         * 
         * @return RenderTexture* 
         */
        virtual RenderTexture *getRenderTexture()                   = 0;

        /**
         * @brief set new RenderTexture
         * 
         * @param render_texture 
         */
        virtual void setRenderTexture(RenderTexture render_texture) = 0;

        /**
         * @brief Get the Global Shape object
         * 
         * @return Vector2d 
         */
        virtual Vector2d getGlobalShape() const                      = 0;

        /**
         * @brief Get the Virtual Shape object
         * 
         * @return Vector2d 
         */
        virtual Vector2d getVirtualShape() const                     = 0;

        /**
         * @brief Get the Field object
         * 
         * @return std::pair<Vector2d, Vector2d> 
         */
        virtual std::pair<Vector2d, Vector2d> getField() const                       = 0;
    };
};