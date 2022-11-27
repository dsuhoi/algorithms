#ifndef __STACK_LIB_HPP__
#define __STACK_LIB_HPP__

#include <cstddef>
#include <cstring>
#include <iostream>
#include <istream>

#include "../metapatterns/base_patterns.hpp"
#include "data_interface.hpp"

template <typename, bool, size_t>
class stack_t;
template <typename T, size_t U = 1024>
using static_stack = stack_t<T, true, U>;
template <typename T, size_t U = 1024>
using dynamic_stack = stack_t<T, false, U>;

// Класс стека
template <typename T, bool is_static, size_t MAX_STACK_SIZE = 1024>
class stack_t : public data_interface<T>
{
    using stack_type = stack_t<T, is_static, MAX_STACK_SIZE>;

public:
    stack_t() : index(0) { constructor(types::int2type<is_static>()); }
    ~stack_t() { destructor(types::int2type<is_static>()); }
    void push(T value) override
    {
        if (index < MAX_STACK_SIZE - 1) stack_data[index++] = value;
    }
    void push_back(T newValue) override { push(newValue); }
    T pop() override
    {
        if (index < 1) return T();
        T value = stack_data[index - 1];
        stack_data[index--] = T();
        return value;
    }
    T pop_back() override { return pop(); }
    T top() override { return stack_data[index]; };
    void clear() override
    {
        while (index > 0) pop();
    }
    size_t size() override { return index; }

    friend std::ostream& operator<<(std::ostream& out, const stack_type& stack_)
    {
        for (size_t _index = 0; _index < stack_.index; ++_index)
            out << stack_.stack_data[_index] << ' ';
        return out;
    }
    friend std::istream& operator>>(std::istream& in, const stack_type& stack_)
    {
        size_t stack_size = 0;
        do
        {
            in >> stack_size;
        } while (stack_size < 1);

        for (size_t _index = 0; _index < stack_size; ++_index)
        {
            T input;
            in >> input;
            stack_.push(input);
        }
    }

    // Создание массива из элементов стека
    T* stack2array(unsigned int& array_len);

private:
    void constructor(types::int2type<true>) {}
    void constructor(types::int2type<false>)
    {
        stack_data = new T[MAX_STACK_SIZE];
    }
    void destructor(types::int2type<true>) {}
    void destructor(types::int2type<false>) { delete[] stack_data; }

    // Стек
    typename types::if_t<is_static, T[MAX_STACK_SIZE], T*>::value stack_data;
    // Позиция последнего элемента в стеке
    size_t index;
};

#endif
