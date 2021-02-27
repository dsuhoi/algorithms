/*
 * data_interface.hpp
 * 
 * Copyright 2020 DSuhoi
 * Интерфейс типов данных.
 * (C++ library)
 */

#ifndef __DATA_INTERFACE_HPP__
#define __DATA_INTERFACE_HPP__

//****************************
// Интерфейс структур данных
//****************************
template <typename T>
class Data_interface
{
public:
	// Установка новых элементов в структуру
	virtual void push(T newValue) = 0;
	virtual void push_back(T newValue) = 0;
	// Удаление элементов из структуры
	virtual T pop() = 0;
	virtual T pop_back() = 0;
	// Вывод последнего элемента
	virtual T top() = 0;
	// Очистка структуры
	virtual void clear() = 0;
	// Получение кол-ва элементов
	virtual size_t size() = 0;
	// Фукнции ввода/вывода
	virtual void print() = 0;
	virtual void scan() = 0;
};

#endif
