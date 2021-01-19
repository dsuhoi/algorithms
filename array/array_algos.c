#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_algos.h"

//********************************
// Функции по работе с массивами
//********************************

// Выделение памяти под одномерный массив длины _len и возвращение указателя на начало массива
TBase *initArr(const TCount _len)
{
	if(_len < 1)
		return NULL;
	
	TBase *arr = malloc(_len*sizeof(TBase));
	
	#ifdef RANDOM_RANGE
		// Заполнение случайными числами
		for(size_t i = 0; i < _len; i++)
			arr[i] = rand() % RANDOM_RANGE;
	#else
		// Обнуление элементов массива
		memset(arr, 0, _len);
	#endif
	
	return arr;
}

// Выделение памяти под двумерный массив (с row кол-вом рядов и column кол-вом слобцов) и возвращение указателя на начало массива
TBase **initArr2(const TCount _row, const TCount _column)
{
	if((_row * _column) < 1)
		return NULL;
	
	// Выделение памяти под элементы и указатели на них
	TBase **arr = malloc(_row * sizeof(TBase*) + _column * _row * sizeof(TBase));
	// Установка первого указателя
	arr[0] = (TCount*) (arr + _row);
	
	for(size_t row = 0; row < _row; row++) {
		// Установка следующих указателей
		arr[row] = arr[0] + _column*row;
		
	#ifdef RANDOM_RANGE
		// Заполнение случайными числами
		for(size_t column = 0; column < _column; column++)
			arr[row][column] = rand() % RANDOM_RANGE;
	#else
		// Обнуление элементов массива
		memset(arr[row], 0, _column);
	#endif
	}
	
	return arr;
}


// Вывод _len элементов массива arr
void printArr(TBase *arr, const TCount _len)
{
	for(size_t i = 0; i < _len; i++) {
		printf(FORMAT_COMMAND, arr[i]); // Вывод элемента
		putchar(DELIM_CHR); // Вывод символа разделителя
	}
	putchar(CARR_CHR);  // Вывод символа перевода каретки
}

// Вывод row строк и _column столбцов элементов массива arr
void printArr2(TBase **arr, const TCount _row, const TCount _column)
{
	for(size_t row = 0; row < _row; row++) {
		for(size_t column = 0; column < _column; column++) {
			printf(FORMAT_COMMAND, arr[row][column]);   // Вывод элемента
			putchar(DELIM_CHR); // Вывод символа разделителя
		}
		putchar(CARR_CHR);  // Вывод символа перевода каретки
	}
}


// Ввод элементов и длины массива (p_len - указатель на длину) и выделение памяти под него
TBase *scanArr(TCount *p_len)
{
	printf("Enter the length of the array: ");
	// Ввод длины массива и проверка вводимых данных
	do {
		scanf(FORMAT_COMMAND_CNT, p_len);
	} while(*p_len < 0);
	// Выделение памяти под массив
	TBase *arr = initArr(*p_len);
	// Ввод элементов
	for(size_t i = 0; i < *p_len; i++) {
		printf("Enter the value [%ld] element: ", i);
		scanf(FORMAT_COMMAND, &arr[i]);
	}
	return arr;
}

// Ввод элементов, кол-ва строк и столбцов массива (p_row и p_column - указатели на кол-во строк и столбцов)
// и выделение памяти под него
TBase **scanArr2(TCount *p_row, TCount *p_column)
{   
	// Ввод кол-ва строк и столбцов и проверка вводимых данных
	printf("Enter the number of rows in the array: ");
	do {
		scanf(FORMAT_COMMAND_CNT, p_row);
	} while(*p_row < 0);
	
	printf("Enter the number of rows in the array: ");
	do {
		scanf(FORMAT_COMMAND_CNT, p_column);
	} while(*p_column < 0);
	
	TBase **arr = initArr2(*p_row, *p_column);
	
	for(size_t row = 0; row < *p_row; row++) {
		for(size_t column = 0; column < *p_column; column++) {
			printf("Enter the value [%ld][%ld] element: ", row, column);    // Ввод элемента
			scanf(FORMAT_COMMAND, &arr[row][column]);
		}
		putchar(CARR_CHR);  // Вывод символа перевода каретки
	}
	return arr;
}


/* Сортировка по функции comp элементов массива arr в диапазоне [_left; _right] (вариант замены sort из стандартной библиотеки)
 * Метод Ч.А.Р. Хоара (1962г)
 */
void quickSortArr(TBase *arr, const TCount _left, const TCount _right, int (*comp)(const TBase, const TBase))
{
	// Условие выхода из рекурсии
	if(_left >= _right)
		return;
	// Перемещение опорного элемента в левый край массива
	swap(&arr[_left], &arr[(_left + _right)/2]);
	// Сохранение индекса крайнего левого (опорного) элемента
	TCount lastLeft = _left;
	// Сортировка с учётом comp
	for(size_t index = _left + 1; index <= _right; index++)
		if(comp(arr[index], arr[_left]) > 0)
			swap(&arr[index], &arr[++lastLeft]);
	// Перемещение опорного элемента за сортируемую область
	swap(&arr[_left], &arr[lastLeft]);
	// Рекурсивный вызов сортировки элементов слудующих частей массива
	quickSortArr(arr, _left, lastLeft - 1, comp);
	quickSortArr(arr, lastLeft + 1, _right, comp);
}


// Сортировка Шелла. Массив arr с длиной len сортируется по функции comp
void shellSortArr(TBase *arr, const TCount len, int (*comp)(const TBase, const TBase))
{
	for(size_t dist = len/2; dist > 0; dist /= 2)
		for(size_t i = 0; i < len - dist; i++)
			for(long j = i; j >= 0 && comp(arr[j], arr[j + dist]) > 0; j -= dist)
				swap(&arr[j], &arr[j + dist]);
}

// Сортировка слиянием. Массив arr с длиной len сортируется по функции comp
void mergeSortArr(TBase *arr, const TCount len, int (*comp)(const TBase, const TBase))
{
	if(len < 2)
		return;
	size_t middle = len/2;
	mergeSort(arr, middle, comp);
	mergeSort(&arr[middle], len/2, comp);
	int *buf = malloc(len * sizeof(int));
	for(size_t left = 0, right = middle, i = 0; i < len; i++)
		if((right >= len) || (left < middle && arr[left] > arr[right]))
			buf[i] = arr[left++];
		else
			buf[i] = arr[right++];
	for(size_t i = 0; i < len; i++)
		arr[i] = buf[i];
	free(buf);
}

// Замена местами элементов под индексами indexA и indexB массива Arr
void swap(TBase *a, TBase *b)
{
	TBase oldElement = *a;
	*a = *b;
	*b = oldElement;
}

// Получение длины строки
size_t _strlen(char *s)
{
	size_t len = 0;
	while(s[len++] != 0);
	return len;
}

// Копирование строк
void _strcpy(char *out, char *in)
{
	while((*(out++) = *(in++)) != 0);
}

// Лексический анализатор (аналог strtok)
char *_strtok(char *src, char *delim)
{
	// Функция сравнение символов разделителей
	int isdelim(char c)
	{
		for(size_t i = 0; i <= _strlen(delim); i++)
			if(c == delim[i])
				return 1;
		return 0;
	}
	
	static char *buf = NULL;
	static size_t index, len;
	if(src != NULL) {
		// Освобождение памяти с прошлых итераций функции
		if(buf != NULL) {
			free(buf);
			buf = NULL;
		}
		// Выделение памяти под буфер, копирование строки в буфер
		len = _strlen(src);
		buf = malloc(len * sizeof(char));
		_strcpy(buf, src);
		index = 0;
	}
	
	// Начало нового слова становится не определено
	size_t left = EOF;
	for(; index <= len; index++) {
		// Если попался символ разделитель, то...
		if(isdelim(buf[index])) {
			// Если это конец слова, то берём случайные две буквы
			if(left >= 0 && (index-1) >= left) {
				buf[index++] = 0;
				return &buf[left];
			}
			// Если после символа(ов) разделителя следует другие символы, то мы отмечаем индекс начала слова
		} else if(left == EOF)
			left = index;
	}
	
	// Освобождение памяти
	if(buf != NULL) {
		free(buf);
		buf = NULL;
	}
	
	return NULL;
}

// Функция смены размерности матрицы arr с old_n X old_m на new_n X new_m
int resizeArr2(TBase ***arr, const TCount old_n, const TCount old_m, const TCount new_n, const TCount new_m)
{
	if(new_m * new_n != old_m * old_n)
		return 1;
	
	TBase *buf = malloc(old_n * old_m * sizeof(TBase));
	for(TCount i = 0; i < old_n; i++)
		for(TCount j = 0; j < old_m; j++)
			buf[old_m*i + j] = (*arr)[i][j];
	free(*arr);
	
	(*arr) = malloc(new_n * sizeof(TBase*) + new_n * new_m * sizeof(TBase));
	(*arr)[0] = (TBase*)((*arr) + new_n);
	for(TCount i = 0; i < new_n; i++) {
		(*arr)[i] = *(arr)[0] + new_m * i;
		for(TCount j = 0; j < new_m; j++)
			(*arr)[i][j] = buf[new_m*i + j];
	}
	
	free(buf);
	return 0;
}
