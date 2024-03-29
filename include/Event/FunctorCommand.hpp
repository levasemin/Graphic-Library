#pragma once

#include "Command.hpp"

namespace SL
{
    template <class ...TParams>
    class FunctorCommand : public Command<TParams...>
    {

    public:
        FunctorCommand(void (*action)(TParams...)) : Command<TParams...>(),
            action_(action) 
        {}

        FunctorCommand(const FunctorCommand &command) = default;
        FunctorCommand &operator= (const FunctorCommand &command) = default; 
        ~FunctorCommand() override = default;
        
        void Execute(TParams... params) override
        {
            action_(params...);
        }
        
    private:
        void (*action_)(TParams...);
    };
}