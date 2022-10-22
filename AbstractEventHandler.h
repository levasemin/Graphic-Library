#pragma once

template <class ...TParams>
class AbstractEventHadler
{
    public:
        virtual void call (TParams ...params) = 0;
    protected:
        AbstractEventHadler() {};
};
