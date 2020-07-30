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


// Вывод _len элементов массива Arr
void ArrPrint(TBase* arr, const TCount _len)
{
	for(size_t i = 0; i < _len; i++){
		printf(FORMAT_COMMAND, arr[i]);	// Вывод элемента
		putchar(DELIM_CHR);	// Вывод символа разделителя
	}
	putchar(CARR_CHR);	// Вывод символа перевода каретки
}

// Вывод row строк и _column столбцов элементов массива Arr
void Arr2Print(TBase** arr, const TCount _row, const TCount _column)
{
	for(size_t row = 0; row < _row; row++){
		for(size_t column = 0; column < _column; column++){
			printf(FORMAT_COMMAND, arr[row][column]);	// Вывод элемента
			putchar(DELIM_CHR);	// Вывод символа разделителя
		}
		putchar(CARR_CHR);	// Вывод символа перевода каретки
	}
}


// Ввод элементов и длины массива (p_len - указатель на длину) и выделение памяти под него
TBase* ArrScanAndCreate(TCount *p_len)
{
	printf("Enter the length of the array: ");
	// Ввод длины массива и проверка вводимых данных
	do{
		scanf(FORMAT_COMMAND_CNT, p_len);
	}while(*p_len<0 || MAX_ARR_SIZE<*p_len);
	// Выделение памяти под массив
	TBase* arr = ArrCreate(*p_len);
	// Ввод элементов
	for(size_t i = 0; i < *p_len; i++){
		printf("Enter the value [%ld] element: ", i);
		scanf(FORMAT_COMMAND, &arr[i]);
	}
	return arr;
}
