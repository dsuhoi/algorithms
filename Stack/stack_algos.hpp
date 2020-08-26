/*
 * stack_algos.hpp
 * 
 * Copyright 2020 DSuhoi
 * Библиотека для работы со стеком
 * (C++ library)
 */

#ifndef __STACK_LIB_HPP__
#define __STACK_LIB_HPP__

#include <iostream>
#include <cstring>

//**************
// Класс стека
//**************
template <typename TBase, size_t MAX_STACK_SIZE>
class StackNode {
private:
	// Стек
	TBase stackData[MAX_STACK_SIZE];
	// Позиция последнего элемента в стеке
	size_t index;
public:
	// Конструктор
	StackNode();
	
	// Создание нового элемента стека
	void Push(TBase newValue);
	// Удаление элемента из стека
	TBase Pop();
	// Вернуть значение последнего элемента
	TBase Top();
	
	// Очистка всего стека
	void Clear();
	// Вернуть размер стека
	size_t Size();
	
	// Вывод стека
	void Print();
	// Ввод стека
	void Scan();
	
	// Создание массива из элементов стека
	TBase *StackToArray(unsigned int &arrayLen);
	
};

//********************************
// Основные функции класса стека
//********************************

// Конструктор
template <typename TBase, size_t MAX_STACK_SIZE>
StackNode<TBase, MAX_STACK_SIZE>::StackNode() : index(0) {}

// Создание нового элемента стека
template <typename TBase, size_t MAX_STACK_SIZE>
void StackNode<TBase, MAX_STACK_SIZE>::Push(TBase newValue)
{
	if(index < MAX_STACK_SIZE - 1){
		stackData[index++] = newValue;
	}
}

// Удаление элемента из стека
template <typename TBase, size_t MAX_STACK_SIZE>
TBase StackNode<TBase, MAX_STACK_SIZE>::Pop()
{
	if(index < 0){
		return TBase();
		
	}
	TBase value = stackData[index];
	stackData[index--] = TBase();
	// Возвращение значения элемента стека
	return value;
}

// Вернуть значение последнего элемента
template <typename TBase, size_t MAX_STACK_SIZE>
TBase StackNode<TBase, MAX_STACK_SIZE>::Top()
{
	return stackData[index];
}

// Очистка всего стека
template <typename TBase, size_t MAX_STACK_SIZE>
void StackNode<TBase, MAX_STACK_SIZE>::Clear()
{
	while(index >= 0){
		Pop();
	}
}

// Вернуть размер стека!
template <typename TBase, size_t MAX_STACK_SIZE>
size_t StackNode<TBase, MAX_STACK_SIZE>::Size()
{
	// Возвращение размера стека
	return (index + 1);
}

// Создание массива из элементов стека
template <typename TBase, size_t MAX_STACK_SIZE>
TBase *StackNode<TBase, MAX_STACK_SIZE>::StackToArray(unsigned int &arrayLen)
{
	// Получение длины будущего массива
	arrayLen = Size();
	// Выделение памяти под массив
	TBase *arr = new TBase[arrayLen];
	// Заполнение массива
	memcpy(arr, stackData, arrayLen * sizeof(TBase));
	// Возвращение указателя на массив
	return arr;
}

// Вывод стека
template <typename TBase, size_t MAX_STACK_SIZE>
void StackNode<TBase, MAX_STACK_SIZE>::Print()
{
	for(size_t _index = 0; _index <= index; _index++){
		std::cout << stackData[_index] << ' ';
	}
	std::cout << std::endl;
}

// Ввод стека
template <typename TBase, size_t MAX_STACK_SIZE>
void StackNode<TBase, MAX_STACK_SIZE>::Scan()
{
	for(size_t _index = 0; _index < MAX_STACK_SIZE; _index++){
		std::cout << "Enter the value [" << _index << "] stack element: ";
		std::cin >> stackData[_index];
	}
}

#endif
