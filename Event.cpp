#include "Event.h"

booba::Event convert_event(const Event &event)
{
    booba::Event booba_event;
    booba_event.type = (booba::EventType)event.type_;
    std::memcpy(&booba_event.Oleg, &event.Oleg_, sizeof(event.Oleg_));

    return booba_event;
}