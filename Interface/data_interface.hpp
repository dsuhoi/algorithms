/*
 * data_interface.hpp
 * 
 * Copyright 2020 DSuhoi
 * Интерфейс типов данных.
 * (C++ library)
 */

#ifndef __DATA_INTERFACE_HPP__
#define __DATA_INTERFACE_HPP__

//******************
// Интерфейс стека
//******************
template <typename T>
class DataInterface {
public:
    virtual void push(T newValue) = 0;
    virtual void pushBack(T newValue) = 0;
    virtual T pop() = 0;
    virtual T popBack() = 0;
    virtual T top() = 0;
    
    virtual void clear() = 0;
    virtual size_t size() = 0;
    
    virtual void print() = 0;
    virtual void scan() = 0;
};

#endif
