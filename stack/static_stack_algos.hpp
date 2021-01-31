/*
 * static_stack_algos.hpp
 * 
 * Copyright 2020 DSuhoi
 * Библиотека для работы со статическим стеком
 * (C++ library)
 */

#ifndef __STAT_STACK_LIB_HPP__
#define __STAT_STACK_LIB_HPP__

#include <iostream>
#include <cstring>
#include "../Interface/data_interface.hpp"

//***************************
// Класс статического стека
//***************************
template <typename T, size_t MAX_STACK_SIZE>
class StatStackNode : DataInterface<T> {
private:
	// Стек
	T stackData[MAX_STACK_SIZE];
	// Позиция последнего элемента в стеке
	size_t index;
public:
	// Конструктор
	StatStackNode();
	
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


//************************************
// Функции класса статического стека
//************************************

// Конструктор
template <typename T, size_t MAX_STACK_SIZE>
StatStackNode<T, MAX_STACK_SIZE>::StatStackNode() : index(0) {}

// Создание нового элемента стека
template <typename T, size_t MAX_STACK_SIZE>
void StatStackNode<T, MAX_STACK_SIZE>::push(T newValue)
{
	if (index < MAX_STACK_SIZE - 1)
		stackData[index++] = newValue;
}

// Удаление элемента из стека
template <typename T, size_t MAX_STACK_SIZE>
T StatStackNode<T, MAX_STACK_SIZE>::pop()
{
	if (index < 0)
		return T();

	T value = stackData[index];
	stackData[index--] = T();
	// Возвращение значения элемента стека
	return value;
}

// Вернуть значение последнего элемента
template <typename T, size_t MAX_STACK_SIZE>
T StatStackNode<T, MAX_STACK_SIZE>::top()
{
	return stackData[index];
}

// Очистка всего стека
template <typename T, size_t MAX_STACK_SIZE>
void StatStackNode<T, MAX_STACK_SIZE>::clear()
{
	while (index >= 0)
		pop();
}

// Вернуть размер стека!
template <typename T, size_t MAX_STACK_SIZE>
size_t StatStackNode<T, MAX_STACK_SIZE>::size()
{
	// Возвращение размера стека
	return (index + 1);
}

// Создание массива из элементов стека
template <typename T, size_t MAX_STACK_SIZE>
T *StatStackNode<T, MAX_STACK_SIZE>::stackToArray(unsigned int &arrayLen)
{
	// Получение длины будущего массива
	arrayLen = size();
	// Выделение памяти под массив
	T *arr = new T[arrayLen];
	// Заполнение массива
	memcpy(arr, stackData, arrayLen * sizeof(T));
	// Возвращение указателя на массив
	return arr;
}

// Вывод стека
template <typename T, size_t MAX_STACK_SIZE>
void StatStackNode<T, MAX_STACK_SIZE>::print()
{
	for (size_t _index = 0; _index <= index; ++_index)
		std::cout << stackData[_index] << ' ';
	std::cout << std::endl;
}

// Ввод стека
template <typename T, size_t MAX_STACK_SIZE>
void StatStackNode<T, MAX_STACK_SIZE>::scan()
{
	for (size_t _index = 0; _index < MAX_STACK_SIZE; ++_index) {
		std::cout << "Enter the value [" << _index << "] stack element: ";
		std::cin >> stackData[_index];
	}
}

#endif
