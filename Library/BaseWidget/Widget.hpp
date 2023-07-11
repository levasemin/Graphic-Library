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

#include "Window.hpp"
#include "Texture.hpp"
#include "RenderTexture.hpp"
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

        Widget() {}
        /**
         * @brief handle left mouse click
         * 
         * @param event 
         */
        virtual void ClickLeftEvent      (const Event &event)          = 0;
        /**
         * @brief 
         * 
         * @param event 
         */
        virtual void ReleasedLeftEvent   (const Event &event)          = 0;              

        /**
         * @brief 
         * 
         * @param event 
         */
        virtual void ClickRightEvent     (const Event &event)          = 0;
        /**
         * @brief 
         * 
         * @param event 
         */
        virtual void ReleasedRightEvent  (const Event &event)          = 0;              
        
        /**
         * @brief 
         * 
         * @param event 
         */
        virtual void MoveMouseEvent      (const Event &event)          = 0;

        /**
         * @brief 
         * 
         * @param event 
         */
        virtual void PressKeyEvent       (const Event &event)          = 0;

        /**
         * @brief 
         * 
         * @param event 
         */
        virtual void ScrollEvent         (const Event &event)          = 0;
        
        /**
         * @brief 
         * 
         * @param event 
         */
        virtual void TextEvent           (const Event &event)          = 0;

        /**
         * @brief 
         * 
         * @param point 
         * @return true 
         * @return false 
         */
        virtual bool point_belonging(Vector2d point) const             = 0;

        /**
         * @brief 
         * 
         */
        virtual void draw()                                            = 0; 

        /**
         * @brief 
         * 
         * @param window 
         */
        virtual void remove(Widget *window)                            = 0;

        /**
         * @brief 
         * 
         * @param window 
         */
        virtual void add(Widget *window)                               = 0;

        /**
         * @brief 
         * 
         * @param window 
         */
        virtual void display(Window *window)                           = 0;

        /**
         * @brief Get the position object
         * 
         * @return Vector2d 
         */
        virtual Vector2d get_position() const                          = 0;
        /**
         * @brief Set the position object
         * 
         * @param position 
         */
        virtual void set_position(Vector2d position)                   = 0;

        virtual Vector2d get_shape() const                             = 0;
        virtual void set_shape(Vector2d shape)                         = 0;

        virtual Widget *get_parent() const                             = 0;
        virtual void set_parent(Widget *parent)                        = 0;

        virtual Texture get_texture() const                            = 0;
        virtual void set_texture(const Texture &texture)               = 0;

        virtual RenderTexture *get_render_texture()                   = 0;
        virtual void set_render_texture(RenderTexture render_texture) = 0;

        virtual Vector2d get_indent() const                            = 0;
        virtual void set_indent(Vector2d)                              = 0;

        virtual Vector2d get_global_shape() const                      = 0;
        virtual void set_global_shape(Vector2d global_shape)           = 0;

        virtual Vector2d get_global_offset() const                     = 0;
        virtual void set_global_offset(Vector2d diff_offset)           = 0;

        virtual Vector2d get_local_offset() const                      = 0;
        virtual void set_local_offset(Vector2d diff_offset)            = 0;

        virtual bool get_has_local_offset()  const                     = 0;
        virtual void set_has_local_offset(bool has)                    = 0;

        virtual Vector2d get_start_field() const                       = 0; 
        virtual Vector2d get_end_field()   const                       = 0;
        
        virtual std::vector<Widget *> get_children() const             = 0;
        virtual void set_children(std::vector<Widget *> children)      = 0;

    protected:
        virtual ~Widget() = default;
    };
};