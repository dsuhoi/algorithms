/*
 * stack_algos.hpp
 *
 * Copyright 2020 DSuhoi
 * Библиотека для работы со стеком
 * (C++ library)
 */

#ifndef __STACK_LIB_HPP__
#define __STACK_LIB_HPP__

#include <cstring>
#include <iostream>
#include <istream>

#include "data_interface.hpp"

template <typename, bool, size_t>
class Stack_node;
// Класс статического стека
template <typename T, size_t U>
using Static_stack_node = Stack_node<T, true, U>;
// Класс динамического стека
template <typename T>
using Dyn_stack_node = Stack_node<T, false, 0>;

// Шаблон выбора типа
template <bool flag, typename T, typename U>
struct Select
{
    using Type = T;
};

template <typename T, typename U>
struct Select<false, T, U>
{
    using Type = U;
};

// Отображение констант
template <int i>
struct Int2type
{
    enum
    {
        value = i
    };
};

//***************************
// Класс стека
//***************************
template <typename T, bool is_static, size_t MAX_STACK_SIZE = 1024>
class Stack_node : public Data_interface<T>
{
    using stack_type = Stack_node<T, is_static, MAX_STACK_SIZE>;

public:
    // Конструктор
    Stack_node() : index(0){};
    // Деструктор
    ~Stack_node() { destructor(Int2type<is_static>()); }
    // Создание нового элемента стека
    void push(T newValue) override { push(newValue, Int2type<is_static>()); };
    // Удаление элемента из стека
    T pop() override { pop(Int2type<is_static>()); };
    // Вернуть значение последнего элемента
    T top() override { return stack_data[index]; };

    // Очистка всего стека
    void clear() override
    {
        while (index > 0) pop();
    };
    // Вернуть размер стека
    size_t size() override { return index + 1; }

    // Вывод стека
    friend std::ostream& operator<<(std::ostream& out, const stack_type& stack_)
    {
        for (size_t _index = 0; _index <= stack_.index; ++_index)
            out << stack_.stack_data[_index] << ' ';
        return out;
    }
    // Ввод стека
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
    void destructor(Int2type<true>) {}

    void destructor(Int2type<false>) { delete[] stack_data; }

    void push(T value, Int2type<true>)
    {
        if (index < MAX_STACK_SIZE - 1) stack_data[index++] = value;
    }

    void push(T value, Int2type<false>)
    {
        T* temp_data = new T[index + 2];
        for (size_t i = 0; i <= index; ++i) temp_data[i] = stack_data[i];
        delete[] stack_data;
        stack_data = temp_data;
        stack_data[index++] = value;
    }

    T pop(Int2type<true>)
    {
        if (index < 0) return T();
        T value = stack_data[index];
        stack_data[index--] = T();
        // Возвращение значения элемента стека
        return value;
    }

    T pop(Int2type<false>)
    {
        if (index < 0) return T();
        T value = stack_data[index];
        T* temp_stack = new T[index];
        for (size_t i = 0; i < index; ++i) temp_stack[i] = stack_data[i];
        delete[] stack_data;
        --index;
        // Возвращение значения элемента стека
        return value;
    }

    // Стек
    typename Select<is_static, T[MAX_STACK_SIZE], T*>::Type stack_data;
    // Позиция последнего элемента в стеке
    size_t index;
};

#endif
