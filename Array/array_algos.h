/*
 * array_algos.h
 * 
 * Copyright 2020 DSuhoi
 * 
 * Библиотека часто используемых функций и алгоритмов
 * для работы с массивами. Функции ввода, вывода, сортировки
 * и т.п.
 * (C library)
 */

#ifndef __ARRAY_LIB_H__
#define __ARRAY_LIB_H__


//*********************************
// Основные типы данных
//*********************************

typedef int TBase;	// искомая переменная (тип данных для массива и т.п.)
typedef int TCount;	// переменная для дополнительных данных (константные аргументы функций и т.п.)
typedef int TBool;	// логический тип данных

//*********************************
// Основные константы
//*********************************
#define True 1			// логическая единица
#define False 0			// логический ноль
#define DELIM_CHR ' '	// символ разделитель
#define CARR_CHR '\n'	// символ перевода каретки
#define FORMAT_COMMAND "%4d"	// команда форматирования
#define FORMAT_COMMAND_CNT "%4d"	// команда форматирования для доп. данных



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
TBase *ArrCreate(const TCount _len);

// Выделение памяти под двумерный массив (с _row кол-вом рядов и _column кол-вом слобцов)
// и возвращение указателя на начало массива
TBase **Arr2Create(const TCount _row, const TCount _column);

/* TBase*** Arr3Create(TCount _row, TCount _column, TCount _height);	// пока не нужен */


// Вывод _len элементов массива Arr
void ArrPrint(TBase *arr, const TCount _len);

// Вывод _row строк и _column столбцов элементов массива Arr
void Arr2Print(TBase **arr, const TCount _row, const TCount _column);


// Ввод элементов и длины массива (p_len - указатель на длину) и выделение памяти под него
TBase *ArrScanAndCreate(TCount *p_len);

// Ввод элементов, кол-ва строк и столбцов массива (p_row и p_column - указатели на кол-во строк и столбцов)
// и выделение памяти под него
TBase **Arr2ScanAndCreate(TCount *p_row, TCount *p_column);


// Сортировка по направлению sortVector (1 - по увеличению, 0 - по уменьшению) 
// элементов массива Arr в диапазоне [_left; _right] (вариант замены sort из стандартной библиотеки)
// Метод Ч.А.Р. Хоара (1962г)
void ArrQuickSort(TBase *arr, const TCount _left, const TCount _right, const TBool sortVector);

// Замена местами элементов под индексами indexA и indexB массива Arr
void ArrSwap(TBase *arr, const TCount indexA, const TCount indexB);

#endif
