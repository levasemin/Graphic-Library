#include "AbstractEventHandler.h"

template<class ObjectHandler, class ...TParams>
class MethodEventHandler : public AbstractEventHadler<TParams ...>
{
    using HandlerMethod = void (ObjectHandler:: *)(TParams... );

    public:
        MethodEventHandler(const ObjectHandler &object_handler) :
            AbstractEventHadler<TParams ...>(),
            object_handler_(object_handler)
            {};
        
        void call (TParams ...params);
    
    private:
        ObjectHandler object_handler_;

};

template<class ObjectHandler, class ...TParams>
void MethodEventHandler<ObjectHandler, TParams...>::call(TParams ...params)
{
    object_handler_(params ...);
}


template<class ObjectHandler, class ...TParams>
AbstractEventHadler<TParams...> &CreateMethodEventHandler(ObjectHandler &object_handler)
{
    AbstractEventHadler<TParams...> *new_handler = (AbstractEventHadler<TParams...> *)new MethodEventHandler<ObjectHandler, TParams ...>(object_handler);
    return *new_handler;
}