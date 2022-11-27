#include "Event.h"

booba::Event convert_event(const Event &event)
{
    booba::Event booba_event;
    
    switch(event.type_)
    {
        case EventType::MouseMoved:
        {
            booba_event.type = booba::EventType::CanvasMMoved;
            booba_event.Oleg.motion.x = (int)event.Oleg_.motion.pos.x_;
            booba_event.Oleg.motion.y = (int)event.Oleg_.motion.pos.y_;
            break;
        }

        case EventType::MousePressed:
        {
            booba_event.type = booba::EventType::CanvasMPressed;
            booba_event.Oleg.mbedata.x = (int)event.Oleg_.mbedata.pos.x_;
            booba_event.Oleg.mbedata.y = (int)event.Oleg_.mbedata.pos.y_;
            
            booba_event.Oleg.mbedata.button = (booba::MouseButton)event.Oleg_.mbedata.button;
            booba_event.Oleg.mbedata.alt    = event.Oleg_.mbedata.alt;
            booba_event.Oleg.mbedata.ctrl   = event.Oleg_.mbedata.ctrl;
            booba_event.Oleg.mbedata.shift  = event.Oleg_.mbedata.shift;
            
            break;
        }

        case EventType::ButtonClicked:
        {
            booba_event.type = booba::EventType::ButtonClicked;
            booba_event.Oleg.bcedata.id = event.Oleg_.bcedata.id;
        }
    }

    return booba_event;
}