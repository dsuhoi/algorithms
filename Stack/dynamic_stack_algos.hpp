/*
 * dynamic_stack_algos.hpp
 * 
 * Copyright 2020 DSuhoi
 * Библиотека для работы с динамическим стеком
 * (C++ library)
 */

#ifndef __DYN_STACK_LIB_HPP__
#define __DYN_STACK_LIB_HPP__

//***************************
// Класс динамического стека
//***************************
template <typename T>
class DynStackNode {
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
    void push(T newValue);
    // Удаление элемента из стека
    T pop();
    // Вернуть значение последнего элемента
    T top();
    
    // Очистка всего стека
    void clear();
    // Вернуть размер стека
    size_t size();
    
    // Вывод стека
    void print();
    // Ввод стека
    void scan();
    
    // Создание массива из элементов стека
    T *stackToArray(unsigned int &arrayLen);
    
};

//*********************************************
// Основные функции класса динамического стека
//*********************************************

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
    stckData[index++] = newValue;
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

// Очистка всего стека
template <typename T>
void DynStackNode<T>::clear()
{
    while(index >= 0)
        pop();
}

#endif
