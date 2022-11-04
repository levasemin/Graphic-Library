#pragma once

#include "Command.h"

template <class Receiver, class ...TParams>
class SimpleCommand : public Command<TParams...>
{

public:
    using Action = void (Receiver:: *)(TParams...);

    SimpleCommand(Receiver *receiver, Action action) : Command<TParams...>(),
        receiver_(receiver),
        action_(action) 
    {

    }

    void Execute(TParams... params) override
    {
        (receiver_->*action_)(params...);
    }

private:
    Receiver *receiver_;
    Action action_;
};