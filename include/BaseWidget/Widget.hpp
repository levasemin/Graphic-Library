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
        friend class Object;
        friend class CompositeObject;

        Widget() {}
        
        virtual Widget &operator= (const Widget &widget)             = default;
        
        virtual ~Widget ()                                           = default;

        virtual void add (Widget *child)                             = 0;

        virtual void remove (Widget *child)                          = 0;

        virtual Vector2d getPosition () const                        = 0;
        virtual void setPosition (Vector2d position)                 = 0;

        virtual Vector2d getShape () const                           = 0;
        virtual void setShape (Vector2d shape)                       = 0;

        virtual Texture getTexture () const                          = 0;
        virtual void setTexture (const Texture &texture)             = 0;

    protected:
        virtual void draw()                                          = 0; 
        virtual void display (Window *window)                        = 0;

        virtual Widget *getParent () const                           = 0;
        virtual void setParent (Widget *parent)                      = 0;

        virtual std::vector<Widget *> getChildren () const           = 0;
        virtual void setChildren (std::vector<Widget *> children)    = 0;

        virtual RenderTexture *getRenderTexture ()                   = 0;
        virtual void setRenderTexture (RenderTexture render_texture) = 0;

        virtual void clickLeftEvent      (const Event &event)        = 0;
    
        virtual void releaseLeftEvent    (const Event &event)        = 0;

        virtual void clickRightEvent     (const Event &event)        = 0;

        virtual void releaseRightEvent   (const Event &event)        = 0;              
        
        virtual void moveMouseEvent      (const Event &event)        = 0;

        virtual void pressKeyEvent       (const Event &event)        = 0;
                    
        virtual void scrollEvent         (const Event &event)        = 0;

        virtual void textEvent           (const Event &event)        = 0;

        virtual bool pointBelong (Vector2d point) const              = 0;

        virtual std::pair<Vector2d, Vector2d> getField () const      = 0;
    };        
};