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
#include "data_interface.hpp"

//***************************
// Класс статического стека
//***************************
template<typename T, size_t MAX_STACK_SIZE>
class Stat_stack_node : public Data_interface<T>
{
public:
	// Конструктор
	Stat_stack_node();

	// Создание нового элемента стека
	void push(T new_value) override;
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
	T* stack_to_array(unsigned int& array_len);
private:
	// Стек
	T stack_data[MAX_STACK_SIZE];
	// Позиция последнего элемента в стеке
	size_t index;
};


//************************************
// Функции класса статического стека
//************************************

// Конструктор
template<typename T, size_t MAX_STACK_SIZE>
Stat_stack_node<T, MAX_STACK_SIZE>::Stat_stack_node() : index(0) {}

// Создание нового элемента стека
template<typename T, size_t MAX_STACK_SIZE>
void Stat_stack_node<T, MAX_STACK_SIZE>::push(T new_value)
{
	if (index < MAX_STACK_SIZE - 1)
		stack_data[index++] = new_value;
}

// Удаление элемента из стека
template<typename T, size_t MAX_STACK_SIZE>
T Stat_stack_node<T, MAX_STACK_SIZE>::pop()
{
	if (index < 0)
		return T();

	T value = stack_data[index];
	stack_data[index--] = T();
	// Возвращение значения элемента стека
	return value;
}

// Вернуть значение последнего элемента
template<typename T, size_t MAX_STACK_SIZE>
T Stat_stack_node<T, MAX_STACK_SIZE>::top()
{
	return stack_data[index];
}

// Очистка всего стека
template<typename T, size_t MAX_STACK_SIZE>
void Stat_stack_node<T, MAX_STACK_SIZE>::clear()
{
	while (index >= 0)
		pop();
}

// Вернуть размер стека!
template<typename T, size_t MAX_STACK_SIZE>
size_t Stat_stack_node<T, MAX_STACK_SIZE>::size()
{
	// Возвращение размера стека
	return (index + 1);
}

// Создание массива из элементов стека
template<typename T, size_t MAX_STACK_SIZE>
T* Stat_stack_node<T, MAX_STACK_SIZE>::stack_to_array(unsigned int& array_len)
{
	// Получение длины будущего массива
	array_len = size();
	// Выделение памяти под массив
	T* arr = new T[array_len];
	// Заполнение массива
	memcpy(arr, stack_data, array_len * sizeof(T));
	// Возвращение указателя на массив
	return arr;
}

// Вывод стека
template<typename T, size_t MAX_STACK_SIZE>
void Stat_stack_node<T, MAX_STACK_SIZE>::print()
{
	for (size_t _index = 0; _index <= index; ++_index)
		std::cout << stack_data[_index] << ' ';
	std::cout << std::endl;
}

// Ввод стека
template<typename T, size_t MAX_STACK_SIZE>
void Stat_stack_node<T, MAX_STACK_SIZE>::scan()
{
	for (size_t _index = 0; _index < MAX_STACK_SIZE; ++_index) {
		std::cout << "Enter the value [" << _index << "] stack element: ";
		std::cin >> stack_data[_index];
	}
}

#endif
