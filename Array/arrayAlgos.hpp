/*
 * arrayAlgos.h
 * 
 * Copyright 2020 DSuhoi
 * 
 * Библиотека часто используемых функций и алгоритмов
 * для работы с массивами. Функции ввода, вывода, сортировки
 * и т.п.
 * (C++ library)
 */

#ifndef __ARRAY_LIB_HPP__
#define __ARRAY_LIB_HPP__

#include <iostream>
#include <ctime>


//*********************************
// Основные константы
//*********************************
#define DELIM_CHR ' '			// символ разделитель


//********************************************
// Основные константы для работы с массивами
//********************************************
#define MAX_ARR_SIZE 1000	// максимальная длина массива
// Для заполнения массивов случайными числами раскомментируйте флаг
// и укажите диапазон для чисел RANDOM_RANGE
#define RANDOM_RANGE 100


//*****************************************
// Основные функции по работе с массивами
//*****************************************

// Выделение памяти под одномерный массив длины _len
// и возвращение указателя на начало массива
/*
 * Освобождение памяти:
 * delete [] arr;
 */
template <class TBase, class TCount>
TBase* ArrCreate(const TCount _len)
{
	if(_len < 1 || MAX_ARR_SIZE < _len){ 
		return nullptr;
	}
	
	TBase* arr = new TBase [_len];
	
	#ifdef RANDOM_RANGE
		// Заполнение случайными числами
		srand(time(NULL));
		for(size_t i = 0; i < _len; i++){
			arr[i] = rand() % RANDOM_RANGE;
		}
	#else
		// Обнуление элементов массива
		memset(arr, 0, _len);
	#endif
	
	return arr;
}

// Выделение памяти под двумерный массив (с _row кол-вом рядов и _column кол-вом слобцов)
// и возвращение указателя на начало массива
/*
 * Освобождение памяти:
 * delete [] arr[0];
 * delete [] arr;
 */
template <class TBase, class TCount>
TBase** Arr2Create(const TCount _row, const TCount _column)
{
	if(((_row * _column) < 1) || (MAX_ARR_SIZE < (_row * _column)) ){
		return nullptr;
	}

	// Выделение памяти под указатели на указатели на элементы
	TBase** arr = new TBase* [_row];
	// Установка первого указателя
	arr[0] = new TBase [_row * _column];
    
	for(size_t row = 0; row < _row; row++){
		// Установка следующих указателей
		arr[row] = arr[0] + _column*row;
    	
	#ifdef RANDOM_RANGE
		// Заполнение случайными числами
		srand(time(NULL));
		for(size_t column = 0; column < _column; column++){
			arr[row][column] = rand() % RANDOM_RANGE;
		}
	#else
		// Обнуление элементов массива
		memset(arr[row], 0, _column);
	#endif
	}
	
	return arr;
}


// Вывод _len элементов массива Arr
template <class TBase, class TCount>
void ArrPrint(TBase* arr, const TCount _len)
{
	for(size_t i = 0; i < _len; i++){
		std::cout << arr[i] << DELIM_CHR;	// Вывод элемента и символа разделителя
	}
	std::cout << std::endl;	// Вывод символа перевода каретки
}

// Вывод _row строк и _column столбцов элементов массива Arr
template <class TBase, class TCount>
void Arr2Print(TBase** arr, const TCount _row, const TCount _column)
{
	for(size_t row = 0; row < _row; row++){
		for(size_t column = 0; column < _column; column++){
			std::cout << arr[row][column] << DELIM_CHR;	// Вывод элемента и символа разделителя
		}
		std::cout << std::endl;	// Вывод символа перевода каретки
	}
}
#endif
