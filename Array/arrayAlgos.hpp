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


// Ввод элементов и длины массива (p_len - указатель на длину) и выделение памяти под него
template <class TBase, class TCount>
TBase* ArrScanAndCreate(TCount *p_len)
{
	std::cout << "Enter the length of the array: ";
	// Ввод длины массива и проверка вводимых данных
	do{
		std::cin >> p_len;
	}while(*p_len<0 || MAX_ARR_SIZE<*p_len);
	// Выделение памяти под массив
	TBase* arr = ArrCreate(*p_len);
	// Ввод элементов
	for(size_t i = 0; i < *p_len; i++){
		std::cout << "Enter the value [" << i << "] element: ";
		std::cin >> arr[i];
	}
	return arr;
}

// Ввод элементов, кол-ва строк и столбцов массива (p_row и p_column - указатели на кол-во строк и столбцов)
// и выделение памяти под него
template <class TBase, class TCount>
TBase** Arr2ScanAndCreate(TCount *p_row, TCount *p_column)
{
	// Ввод кол-ва строк и столбцов и проверка вводимых данных
	std::cout << "Enter the number of rows in the array: ";
	do{
		std::cin >> p_row;
	}while(*p_row<0 || MAX_ARR_SIZE<*p_row);
	
	std::cout << "Enter the number of rows in the array: ";
	do{
		std::cin >> p_column;
	}while(*p_column<0 || MAX_ARR_SIZE<*p_column);
	
	TBase** arr = Arr2Create(*p_row, *p_column);
	
	for(size_t row = 0; row < *p_row; row++){
		for(size_t column = 0; column < *p_column; column++){
			std::cout << "Enter the value [" << row << "][" << column << "] element: ";	// Ввод элемента
			std::cin << arr[row][column];
		}
		std::cout << std::endl;	// Вывод символа перевода каретки
	}
	return arr;
}


// Сортировка по направлению sortVector (1 - по увеличению, 0 - по уменьшению) 
// элементов массива Arr в диапазоне [_left; _right] (вариант замены sort из стандартной библиотеки)
// Метод Ч.А.Р. Хоара (1962г)
template <class TBase, class TCount>
void ArrQuickSort(TBase* arr, const TCount _left, const TCount _right, bool sortVector)
{
	// Условие выхода из рекурсии
	if(_left>=_right) return;
	// Перемещение опорного элемента в левый край массива
	ArrSwap(arr, _left, (_left + _right)/2);
	// Сохранение индекса крайнего левого (опорного) элемента
	TCount lastLeft = _left;
	// Сортировка с учётом направления sortVector
	for(size_t index = _left+1; index<=_right; index++)
		if( (arr[index]<arr[_left] && sortVector==true) ||
			(arr[index]>arr[_left] && sortVector==false) ){
			ArrSwap(arr, index, ++lastLeft);
		}
	// Перемещение опорного элемента за сортируемую область
	ArrSwap(arr, _left, lastLeft);
	// Рекурсивный вызов сортировки элементов слудующих частей массива
	ArrQuickSort(arr, _left, lastLeft-1, sortVector);
	ArrQuickSort(arr, lastLeft+1, _right, sortVector);
}

// Замена местами элементов под индексами indexA и indexB массива Arr
template <class TBase, class TCount>
void ArrSwap(TBase* arr, const TCount indexA, const TCount indexB)
{
	TBase oldElement = arr[indexB];
	arr[indexB] = arr[indexA];
	arr[indexA] = oldElement;
}

#endif
