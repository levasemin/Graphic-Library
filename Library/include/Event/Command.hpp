#pragma once

namespace SL
{
    template<class ...Tparams>
    class Command
    {
    public:
        virtual void Execute(Tparams... params) = 0;
        virtual ~Command() = default; 
    };
}