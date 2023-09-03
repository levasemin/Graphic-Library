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

#include "RenderTexture.hpp"
#include "Window.hpp"
#include "Vector2d.hpp"
#include "Event.hpp"

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
        
        /**
         * @brief Destroy the Widget object
         * 
         */
        virtual ~Widget () = default;

        /**
         * @brief Add object as a new child.
         * @details Method create dependences of spreading events and position. 
         *          Child will be created in parent, it's position is relative to the parent's start and child will get every event after parent.
         *           
         * @param child object for adding.
         */
        virtual void add (Widget *child)                             = 0;
        
        /** Remove child from object.
         * @brief Method delete dependences of spreading events and position.
         * 
         * @param child object for removing.
         */
        virtual void remove (Widget *child)                          = 0;

        /**
         * @brief Get the shape of object.
         * 
         * @return Vector2d x coordinate is width, y is height. 
         */
        virtual Vector2d getShape () const                           = 0;

        /**
         * @brief Set the shape of object.
         * 
         * @param shape Vector2d x coordinate is width, y is height. 
         */
        virtual void setShape (Vector2d shape)                       = 0;

        /**
         * @brief get the position of object.
         * @details coordinates of object's left corner.
         * @return Vector2d.
         */
        virtual Vector2d getPosition () const                        = 0;

        /**
         * @brief Set the position of object
         * 
         * @param position coordinates of object's left corner.
         */
        virtual void setPosition (Vector2d position)                 = 0;
        
        /**
         * @brief Get the Texture of object.
         * 
         * @return Texture 
         */
        virtual Texture getTexture () const                          = 0;
        
        /**
         * @brief Set the Texture of object.
         * 
         * @param texture 
         */
        virtual void setTexture (const Texture &texture)             = 0;

        /**
         * @brief Get the color of object
         * @details get color of object's sprite.
         * @return Color 
         */
        virtual Color getColor() const                               = 0;
        
        /**
         * @brief Set the Color object
         * @details set color to object's sprite.
         * @param color 
         */
        virtual void setColor(Color color)                           = 0;
        
    protected:
        /**
         * @brief Draw object.
         * 
         */
        virtual void draw()                                          = 0; 
        
        /**
         * @brief Display object on screen what has been rendered to the window so far.
         * 
         * @param window 
         */
        virtual void display (Window *window)                        = 0;

        /**
         * @brief Get the parent of object
         * 
         * @return Widget* pointer pon parent.
         */
        virtual Widget *getParent () const                           = 0;
        /**
         * @brief Set the parent of object.
         * 
         * @param parent pointer on parent.
         */
        virtual void setParent (Widget *parent)                      = 0;

        /**
         * @brief Get the children of object
         * 
         * @return std::vector<Widget *> vector of pointers on children. 
         */
        virtual std::vector<Widget *> getChildren () const           = 0;
        
        /**
         * @brief Get the pointer on object's Render Texture
         * @details render texture is canvas, that is drawn on display.
         *          It is a real appearance of object with his texture and textures his child on this. 
         *          Also it is redrawn after spreading event for being actual every time. 
         * @return RenderTexture* pointer on actual object's RenderTexture.
         */
        virtual RenderTexture *getRenderTexture ()                   = 0;
        
        /**
         * @brief get the object's Field.
         * @details get the real object's left and right corners considering parent overlap.
         * @return std::pair<Vector2d, Vector2d> 
         */
        virtual std::pair<Vector2d, Vector2d> getField () const      = 0;
        
        /**
         * @brief check belonging point to this object. 
         * 
         * @param point 
         * @return true belonging.
         * @return false not belonging.
         */
        virtual bool pointBelong (Vector2d point) const              = 0;

        /**
         * @brief Handle mouse's moving.
         * @details Method will be called every time when mouse will be moved.
         * @param event Detail information of event is MotionEventData metion in event's union Oleg_.
         */
        virtual void moveMouseEvent      (const Event &event)        = 0;
        
        /**
         * @brief Handle mouse's clicking.
         * @details Method will be called every time when mouse's button will be clicked.
         * @param event Detail information of event is MousePressedEventData mpedata in event's union Oleg_.
         */
        virtual void clickEvent      (const Event &event)        = 0;
        
        /**
         * @brief Handle mouse's releasing.
         * @details Method will be called every time when mouse's button will be released.
         * @param event Detail information of event is MouseReleasedEventData mredata in event's union Oleg_.
         */
        virtual void releaseEvent    (const Event &event)        = 0;
        
        /**
         * @brief Handle mouse's scrolling.
         * @details Method will be called every time when mouse's scroll button will be scroll.
         * @param event Detail information of event is MouseScrolledEventData msedata in event's union Oleg_.
         */
        virtual void scrollEvent         (const Event &event)        = 0;

        /**
         * @brief Handle keyboard's click.
         * @details Method will be called every time when keyboard will be clicked.
         * @param event Detail information of event is KeyPressedEventData kpedata in event's union Oleg_.
         */
        virtual void pressKeyEvent       (const Event &event)        = 0;            

        /**
         * @brief Handle text.
         * @details Method will be called every time when character will be typed.
         * @param event Detail information of event is TextEventData tedata in event's union Oleg_.
         */
        virtual void textEvent           (const Event &event)        = 0;
    };        
};