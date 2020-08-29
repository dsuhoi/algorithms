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
template <typename T, size_t MAX_STACK_SIZE>
class DynStackNode {
private:
    // Стек
    T *stackData;
    // Позиция последнего элемента в стеке
    size_t index;
    
    void _realloc(T *_stack);
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
DynStackNode::DynStackNode()
{
    stackData = nullptr;
    index = 0;
}

// Деструктор
DynStackNode::~DynStackNode()
{
    
}


#endif
