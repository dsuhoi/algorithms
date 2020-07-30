#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arrayAlgos.h"


//*****************************************
// Основные функции по работе с массивами
//*****************************************

// Выделение памяти под одномерный массив длины _len и возвращение указателя на начало массива
TBase* ArrCreate(const TCount _len)
{
	TBase* arr = (TBase*) malloc(_len*sizeof(TBase));
	
	#ifdef RANDOM_RANGE
		// Заполнение случайными числами
		srand(time(NULL));
		for(size_t i = 0; i < _len; i++)
			arr[i] = rand() % RANDOM_RANGE;
	#else
		// Обнуление элементов массива
		memset(arr, 0, _len);
	#endif
	
	return arr;
}

// Выделение памяти под двумерный массив (с row кол-вом рядов и column кол-вом слобцов) и возвращение указателя на начало массива
TBase** Arr2Create(const TCount _row, const TCount _column)
{
	// Выделение памяти под элементы и указатели на них
	TBase** arr = (TBase**) malloc(_row*sizeof(TBase*) + _column*_row*sizeof(TBase));
	// Установка первого указателя
    arr[0] = (TCount*) (arr + _row);
    
    for(size_t row = 0; row < _row; row++){
		// Установка следующих указателей
    	arr[row] = arr[0] + _column*row;
    	
    #ifdef RANDOM_RANGE
		// Заполнение случайными числами
		srand(time(NULL));
		for(size_t column = 0; column < _column; column++)
			arr[row][column] = rand() % RANDOM_RANGE;
	#else
		// Обнуление элементов массива
		memset(arr[row], 0, _column);
	#endif
    }
    
    return arr;
}
