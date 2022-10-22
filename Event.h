#pragma once

#include "AbstractEventHandler.h"
#include <vector>
#include <iostream>

template <class ...TParams>
class Event
{
    using EventHandler = AbstractEventHadler<TParams ...>;
    
    public:
        Event() {};
        
        ~Event() {};

        void operator() (TParams ...params);
        void operator+= (EventHandler &eventhandler);

    private:
        std::vector<EventHandler *> handlers_ = std::vector<EventHandler *>();
};


template <class ...TParams>
void Event<TParams...>::operator() (TParams ...params)
{
    for (int i = 0; i < handlers_.size(); i++)
    {
        handlers_[i]->call(params ...);
    }
}

template <class ...TParams>
void Event<TParams...>::operator+= (EventHandler &eventhandler)
{
    handlers_.push_back(&eventhandler);
}