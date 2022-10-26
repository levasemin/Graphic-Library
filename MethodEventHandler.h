#pragma once
#include "AbstractEventHandler.h"

template<class ObjectHandler, class ...TParams>
class MethodEventHandler : public AbstractEventHadler<TParams ...>
{
    using HandlerMethod = void (ObjectHandler:: *)(TParams... );

    public:
        MethodEventHandler(const ObjectHandler &object_handler, HandlerMethod handler_method) :
            AbstractEventHadler<TParams ...>(),
            object_handler_(object_handler),
            handler_method_(handler_method)
            {};
        
        void call (TParams ...params)
        {
            (object_handler_.*handler_method_)(params ...);
        }
    
    private:
        ObjectHandler object_handler_;
        HandlerMethod handler_method_;
};

template<class ObjectHandler, class ...TParams>
AbstractEventHadler<TParams...> &CreateMethodEventHandler(ObjectHandler &object_handler, void (ObjectHandler::*method)(TParams ...))
{
    AbstractEventHadler<TParams...> *new_handler = (AbstractEventHadler<TParams...> *)new MethodEventHandler<ObjectHandler, TParams ...>(object_handler, method);
    return *new_handler;
}