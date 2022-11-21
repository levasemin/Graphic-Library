#pragma once

#include "Command.h"
#include "tools.h"
#include "Event.h"

template <class Receiver>
class ToolCommand : public Command<const booba::Event &>
{

public:
    using Action = void (Receiver:: *)(booba::Image *, const booba::Event *);

    ToolCommand(Receiver *receiver, Action action) : Command<const booba::Event &>(),
        receiver_(receiver),
        action_(action) 
    {

    }

    void Execute(const booba::Event &event) override
    {
        (receiver_->*action_)(nullptr, &event);
    }

private:
    Receiver *receiver_;
    Action action_;
};