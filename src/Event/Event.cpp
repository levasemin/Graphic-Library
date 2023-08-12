#include "Event.hpp"

namespace SL
{
    Event::Event ():
            type_(EventType::NoEvent),
            Oleg_({})
            {}
        
    Event::Event(const sf::Event& sfEvent) :
        type_(EventType::NoEvent),
        Oleg_({})
    {   
        switch (sfEvent.type)
        {
            case sf::Event::Closed:
            {
                type_ = EventType::Closed;
                
                break;
            }

            case sf::Event::MouseMoved:
            {
                type_ = EventType::MouseMoved;
                Oleg_.metion.pos = Vector2d(static_cast<float>(sfEvent.mouseMove.x), static_cast<float>(sfEvent.mouseMove.y));

                break;
            }

            case sf::Event::MouseButtonPressed:
            {
                type_ = EventType::MousePressed;

                if (sfEvent.mouseButton.button == sf::Mouse::Button::Left)
                {
                    Oleg_.mpedata.button = MouseButton::Left;
                }

                else if (sfEvent.mouseButton.button == sf::Mouse::Button::Right)
                {
                    Oleg_.mpedata.button = MouseButton::Right;
                }

                Oleg_.mpedata.pos = Vector2d(static_cast<float>(sfEvent.mouseButton.x), static_cast<float>(sfEvent.mouseButton.y));

                break; 
            }

            case sf::Event::MouseButtonReleased:
            {
                type_ = EventType::MouseReleased;

                if (sfEvent.mouseButton.button == sf::Mouse::Button::Left)
                {
                    Oleg_.mredata.button = MouseButton::Left;
                }

                else if (sfEvent.mouseButton.button == sf::Mouse::Button::Right)
                {
                    Oleg_.mredata.button = MouseButton::Left;
                }

                Oleg_.mredata.pos = Vector2d(static_cast<float>(sfEvent.mouseButton.x), static_cast<float>(sfEvent.mouseButton.y));
                
                break;
            }

            case sf::Event::TextEntered:
            {
                if (31 < sfEvent.text.unicode && sfEvent.text.unicode < 128)
                {
                    type_ = EventType::textEvent;
                    Oleg_.tedata.letter = static_cast<char>(sfEvent.text.unicode);
                }
                break;
            }

            case sf::Event::KeyPressed:
            {
                type_ = EventType::KeyPressed;

                Oleg_.kpedata.code = (Key)sfEvent.key.code;

                if (sfEvent.key.alt)
                {
                    Oleg_.kpedata.alt = true;
                }

                if (sfEvent.key.control)
                {
                    Oleg_.kpedata.ctrl = true;
                }

                if (sfEvent.key.shift)
                {
                    Oleg_.kpedata.shift = true;
                }

                break;
            }

            case sf::Event::MouseWheelScrolled:
            {
                type_ = EventType::MouseWheelScrolled;
                Oleg_.mwsedata.value = sfEvent.mouseWheelScroll.delta;
                Oleg_.mwsedata.pos = Vector2d(static_cast<float>(sfEvent.mouseWheelScroll.x), static_cast<float>(sfEvent.mouseWheelScroll.y));
                break;
            }

            case sf::Event::Count:
            case sf::Event::Resized:
            case sf::Event::LostFocus:
            case sf::Event::GainedFocus:
            case sf::Event::KeyReleased:
            case sf::Event::MouseWheelMoved:
            case sf::Event::MouseEntered:
            case sf::Event::MouseLeft:
            case sf::Event::JoystickButtonPressed:
            case sf::Event::JoystickButtonReleased:
            case sf::Event::JoystickConnected:
            case sf::Event::JoystickDisconnected:
            case sf::Event::JoystickMoved:
            case sf::Event::TouchBegan:
            case sf::Event::TouchMoved:
            case sf::Event::TouchEnded:
            case sf::Event::SensorChanged:
            default:
                break;
        }
    }
}