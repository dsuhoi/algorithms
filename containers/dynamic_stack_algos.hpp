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
#include "data_interface.hpp"

//***************************
// Класс динамического стека
//***************************
template<typename T>
class Dyn_stack_node : public Data_interface<T>
{
public:
	// Конструктор
	Dyn_stack_node();
	// Деструктор
	~Dyn_stack_node();
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
	T* stack_to_array(unsigned int& array_len);
private:
	// Стек
	T* stack_data;
	// Позиция последнего элемента в стеке
	size_t index;
};

//*************************************
// Функции класса динамического стека
//*************************************

// Конструктор
template<typename T>
Dyn_stack_node<T>::Dyn_stack_node()
{
	stack_data = nullptr;
	index = 0;
}

// Деструктор
template<typename T>
Dyn_stack_node<T>::~Dyn_stack_node()
{
	delete [] stack_data;
}

// Создание нового элемента стека
template<typename T>
void Dyn_stack_node<T>::push(T newValue)
{
	T* temp_data = new T[index + 2];
	for (size_t i = 0; i <= index; ++i)
		temp_data[i] = stack_data[i];
	delete [] stack_data;
	stack_data = temp_data;
	stack_data[index++] = newValue;
}

// Удаление элемента из стека
template<typename T>
T Dyn_stack_node<T>::pop()
{
	if (index < 0)
		return T();
	T value = stack_data[index];
	T* temp_stack = new T[index];
	for (size_t i = 0; i < index; ++i)
		temp_stack[i] = stack_data[i];
	delete [] stack_data;
	--index;
	// Возвращение значения элемента стека
	return value;
}

// Вернуть значение последнего элемента
template<typename T>
T Dyn_stack_node<T>::top()
{
	return stack_data[index];
}

// Очистка всего стека
template<typename T>
void Dyn_stack_node<T>::clear()
{
	while (index >= 0)
		pop();
}

// Вернуть размер стека
template<typename T>
size_t Dyn_stack_node<T>::size()
{
	return (index + 1);
}

// Вывод стека
template<typename T>
void Dyn_stack_node<T>::print()
{
	for (size_t _index = 0; _index <= index; ++_index)
		std::cout << stack_data[_index] << ' ';
	std::cout << std::endl;
}

// Ввод стека
template<typename T>
void Dyn_stack_node<T>::scan()
{
	std::cout << "Enter the number of stack elements: ";
	size_t stack_size;

	do {
		std::cin >> stack_size;
	} while (stack_size < 1);

	for (size_t _index = 0; _index < stack_size; ++_index) {
		std::cout << "Enter the value [" << _index << "] stack element: ";
		T input;
		std::cin >> input;
		push(input);
	}
}
#endif
