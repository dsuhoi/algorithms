#ifndef __DATA_INTERFACE_HPP__
#define __DATA_INTERFACE_HPP__

#include <iostream>

// Интерфейс структур данных
template <typename T>
struct data_interface
{
    virtual void push(T newValue) = 0;
    virtual void push_back(T newValue) = 0;
    virtual T pop() = 0;
    virtual T pop_back() = 0;
    virtual T top() = 0;
    virtual void clear() = 0;
    virtual size_t size() = 0;
};

#endif
