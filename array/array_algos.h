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


//**************
// Типы данных
//**************

typedef int TBase;  // Искомая переменная (тип данных для массива и т.п.)
typedef int TCount; // Переменная для дополнительных данных (константные аргументы функций и т.п.)
typedef int TBool;  // Логический тип данных

//************
// Константы
//************
#define True 1                   // Логическая единица
#define False 0                  // Логический ноль
#define DELIM_CHR ' '            // Символ разделитель
#define CARR_CHR '\n'            // Символ перевода каретки
#define FORMAT_COMMAND "%4d"     // Команда форматирования
#define FORMAT_COMMAND_CNT "%4d" // Команда форматирования для доп. данных



//***********************************
// Константы для работы с массивами
//***********************************
#define MAX_ARR_SIZE 1000   // Максимальная длина массива
// Для заполнения массивов случайными числами раскомментируйте флаг
// и укажите диапазон для чисел RANDOM_RANGE
#define RANDOM_RANGE 100



//********************************
// Функции по работе с массивами
//********************************

// Выделение памяти под одномерный массив длины _len
// и возвращение указателя на начало массива
TBase *initArr(const TCount _len);

// Выделение памяти под двумерный массив (с _row кол-вом рядов и _column кол-вом слобцов)
// и возвращение указателя на начало массива
TBase **initArr2(const TCount _row, const TCount _column);

/* TBase*** Arr3Create(TCount _row, TCount _column, TCount _height);    // пока не нужен */


// Вывод _len элементов массива Arr
void printArr(TBase *arr, const TCount _len);

// Вывод _row строк и _column столбцов элементов массива Arr
void printArr2(TBase **arr, const TCount _row, const TCount _column);


// Ввод элементов и длины массива (p_len - указатель на длину) и выделение памяти под него
TBase *scanArr(TCount *p_len);

// Ввод элементов, кол-ва строк и столбцов массива (p_row и p_column - указатели на кол-во строк и столбцов)
// и выделение памяти под него
TBase **scanArr2(TCount *p_row, TCount *p_column);


// Сортировка по направлению sortVector (1 - по увеличению, 0 - по уменьшению) 
// элементов массива Arr в диапазоне [_left; _right] (вариант замены sort из стандартной библиотеки)
// Метод Ч.А.Р. Хоара (1962г)
void quickSortArr(TBase *arr, const TCount _left, const TCount _right, int (*comp)(const TBase, const TBase));

// Замена местами элементов под индексами indexA и indexB массива Arr
void swapArr(TBase *arr, const TCount indexA, const TCount indexB);

#endif
