#pragma once
#include "AbstractEventHandler.h"

template<class ...TParams>
class FunctionEventHandler : public AbstractEventHadler<TParams ...>
{
    public: 
        FunctionEventHandler(void (*function)(TParams ...)) :
            AbstractEventHadler<TParams ...>(),
            function_(function)
            {};
        
        void call (TParams ...params)
        {
            (*function_)(params ...);
        }
    
    private:
        void (*function_)(TParams ...);
};


template<class ...TParams>
AbstractEventHadler<TParams ...> &CreateFunctionEventHandler(void (*function)(TParams ...))
{
    AbstractEventHadler<TParams ...> *new_handler = (AbstractEventHadler<TParams ...> *)new FunctionEventHandler<TParams ...>(function);
    return *new_handler;
}