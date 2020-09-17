/*
 * dynamic_stack_algos.hpp
 * 
 * Copyright 2020 DSuhoi
 * Библиотека для работы с динамическим стеком
 * (C++ library)
 */

#ifndef __DYN_STACK_LIB_HPP__
#define __DYN_STACK_LIB_HPP__

#include <iostream>
#include <cstring>
#include "../Interface/data_interface.hpp"

//***************************
// Класс динамического стека
//***************************
template <typename T>
class DynStackNode : DataInterface<T>{
private:
    // Стек
    T *stackData;
    // Позиция последнего элемента в стеке
    size_t index;
    
public:
    // Конструктор
    DynStackNode();
    // Деструктор
    ~DynStackNode();
    // Создание нового элемента стека
    void push(T newValue) override;
    // Удаление элемента из стека
    T pop() override;
    // Вернуть значение последнего элемента
    T top() override;
    
    // Очистка всего стека
    void clear() override;
    // Вернуть размер стека
    size_t size() override;
    
    // Вывод стека
    void print() override;
    // Ввод стека
    void scan() override;
    
    // Создание массива из элементов стека
    T *stackToArray(unsigned int &arrayLen);
};

//*************************************
// Функции класса динамического стека
//*************************************

// Конструктор
template <typename T>
DynStackNode<T>::DynStackNode()
{
    stackData = nullptr;
    index = 0;
}

// Деструктор
template <typename T>
DynStackNode<T>::~DynStackNode()
{
    delete [] stackData;
}

// Создание нового элемента стека
template <typename T>
void DynStackNode<T>::push(T newValue)
{
    T *tempData = new T[index + 2];
    for(size_t i = 0; i <= index; i++)
        tempData[i] = stackData[i];
    delete [] stackData;
    stackData = tempData;
    stackData[index++] = newValue;
}

// Удаление элемента из стека
template <typename T>
T DynStackNode<T>::pop()
{
    if(index < 0)
        return T();
    T value = stackData[index];
    T *tempStack = new T[index];
    for(size_t i = 0; i < index; i++)
        tempStack[i] = stackData[i];
    delete [] stackData;
    --index;
    // Возвращение значения элемента стека
    return value;
}

// Вернуть значение последнего элемента
template <typename T>
T DynStackNode<T>::top()
{
    return stackData[index];
}

// Очистка всего стека
template <typename T>
void DynStackNode<T>::clear()
{
    while(index >= 0)
        pop();
}

// Вернуть размер стека
template <typename T>
size_t DynStackNode<T>::size()
{
    return (index + 1);
}

// Вывод стека
template <typename T>
void DynStackNode<T>::print()
{
    for(size_t _index = 0; _index <= index; _index++)
        std::cout << stackData[_index] << ' ';
    std::cout << std::endl;
}

// Ввод стека
template <typename T>
void DynStackNode<T>::scan()
{
    std::cout << "Enter the number of stack elements: ";
    size_t stackSize;
    
    do {
        std::cin >> stackSize;
    } while(stackSize < 1);
    
    for(size_t _index = 0; _index < stackSize; _index++) {
        std::cout << "Enter the value [" << _index << "] stack element: ";
        T input;
        std::cin >> input;
        push(input);
    }
}
#endif
