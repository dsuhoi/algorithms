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
#include "data_interface.hpp"


template<typename, bool, size_t> class Stack_node;
// Класс статического стека 
template<typename T, size_t U> 
using Static_stack_node = Stack_node<T, true, U>;
// Класс динамического стека
template<typename T>
using Dyn_stack_node = Stack_node<T, false, 0>;


// Шаблон выбора типа
template<bool flag, typename T, typename U>
struct Select
{
	using Type = T;
};

template<typename T, typename U>
struct Select<false, T, U>
{
	using Type = U;
};

// Отображение констант
template<int i>
struct Int2type
{
	enum { value = i };
};


//***************************
// Класс стека
//***************************
template<typename T, bool is_static, size_t MAX_STACK_SIZE = 1024>
class Stack_node : public Data_interface<T>
{
public:
	// Конструктор
	Stack_node();
	// Деструктор
	~Stack_node();
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
	T* stack2array(unsigned int& array_len);
private:
	void destructor(Int2type<true>)
	{}
	
	void destructor(Int2type<false>) 
	{
		delete [] stack_data;
	}

	void push(T value, Int2type<true>)
	{
		if (index < MAX_STACK_SIZE - 1)
			stack_data[index++] = value;
	}
	
	void push(T value, Int2type<false>)
	{
		T* temp_data = new T[index + 2];
		for (size_t i = 0; i <= index; ++i)
			temp_data[i] = stack_data[i];
		delete [] stack_data;
		stack_data = temp_data;
		stack_data[index++] = value;
	}

	T pop(Int2type<true>)
	{
		if (index < 0)
			return T();
		T value = stack_data[index];
		stack_data[index--] = T();
		// Возвращение значения элемента стека
		return value;
	}

	T pop(Int2type<false>)
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

	// Стек
	typename Select<is_static, T[MAX_STACK_SIZE], T*>::Type stack_data;
	// Позиция последнего элемента в стеке
	size_t index;
};

//*************************************
// Функции класса стека
//*************************************

// Конструктор
template<typename T, bool is_static, size_t MAX_STACK_SIZE>
Stack_node<T, is_static, MAX_STACK_SIZE>::Stack_node() : index(0)
	{}

// Деструктор
template<typename T, bool is_static, size_t MAX_STACK_SIZE>
Stack_node<T, is_static, MAX_STACK_SIZE>::~Stack_node()
{
	destructor(Int2type<is_static>());
}

// Создание нового элемента стека
template<typename T, bool is_static, size_t MAX_STACK_SIZE>
void Stack_node<T, is_static, MAX_STACK_SIZE>::push(T value)
{
	push(value, Int2type<is_static>());
}

// Удаление элемента из стека
template<typename T, bool is_static, size_t MAX_STACK_SIZE>
T Stack_node<T, is_static, MAX_STACK_SIZE>::pop()
{
	return pop(Int2type<is_static>());
}

// Вернуть значение последнего элемента
template<typename T, bool is_static, size_t MAX_STACK_SIZE>
T Stack_node<T, is_static, MAX_STACK_SIZE>::top()
{
	return stack_data[index];
}

// Очистка всего стека
template<typename T, bool is_static, size_t MAX_STACK_SIZE>
void Stack_node<T, is_static, MAX_STACK_SIZE>::clear()
{
	while (index >= 0)
		pop();
}

// Вернуть размер стека
template<typename T, bool is_static, size_t MAX_STACK_SIZE>
size_t Stack_node<T, is_static, MAX_STACK_SIZE>::size()
{
	return (index + 1);
}

// Вывод стека
template<typename T, bool is_static, size_t MAX_STACK_SIZE>
void Stack_node<T, is_static, MAX_STACK_SIZE>::print()
{
	for (size_t _index = 0; _index <= index; ++_index)
		std::cout << stack_data[_index] << ' ';
	std::cout << std::endl;
}

// Ввод стека
template<typename T, bool is_static, size_t MAX_STACK_SIZE>
void Stack_node<T, is_static, MAX_STACK_SIZE>::scan()
{
	std::cout << "Enter the number of stack elements: ";
	size_t stack_size;

	do
    {
		std::cin >> stack_size;
	} while (stack_size < 1);

	for (size_t _index = 0; _index < stack_size; ++_index)
	{
		std::cout << "Enter the value [" << _index << "] stack element: ";
		T input;
		std::cin >> input;
		push(input);
	}
}


#endif
