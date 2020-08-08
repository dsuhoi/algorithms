#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listAlgos.h"


//*****************************************************
// Основные функции по работе с односвязными списками
//*****************************************************

// Создание списка и его первого узла
ListNode *InitList(const TBase newValue)
{
	// Выделение памяти под первый узел и присвоение значений
	ListNode *headNode = (ListNode*) malloc(sizeof(ListNode));
	headNode->value = newValue;
	return headNode;
}

// Создание списка с numNode количеством узлов (заполнены случайными числами)
ListNode *GenerateList(const TCount numNode)
{
	ListNode *headNode = InitList(0);	// Первый элемент является нулевым
	#ifdef RANDOM_RANGE
		srand(time(NULL));
	#endif
	// Если заполнение случайными числами отключено, то заполняем узлы 0
	for(size_t index = 1; index < numNode; index++){
		#ifdef RANDOM_RANGE
			PushBackList(headNode, rand() % RANDOM_RANGE);
		#else
			PushBackList(headNode, 0);
		#endif
	}
	return headNode;
}


// Вставить узел со значением newValue в начало списка с вершиной headNode
void PushList(ListNode** headNode, TBase newValue)
{
	// Выделение памяти под первый узел и присвоение значений
	ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
	newNode->value = newValue;
	// Смена указателя на верхний узел
	newNode->p_nextNode = (*headNode);
	// Перестановка указателя на новый верхний узел
	(*headNode) = newNode;
}

// Вставить узел со значением newValue в конец списка с вершиной headNode
void PushBackList(ListNode* headNode, TBase newValue)
{
	// Выделение памяти под первый узел и присвоение значений
	ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
	newNode->value = newValue;
	newNode->p_nextNode = NULL;
	// Получение указателя на последний узел
	ListNode *lastNode = GetLastList(headNode);
	lastNode->p_nextNode = newNode;
}


// Удалить начальный узел из списка с вершиной headNode
TBase PopList(ListNode **headNode)
{
	// Проверка на наличие узлов в списке
	if(headNode == NULL){ 
		return 0;
	}
	// Создание указателя на вершину списка
	ListNode *lastNode = (*headNode);
	TBase lastValue = lastNode->value;
	(*headNode) = (*headNode)->p_nextNode;
	// Удаление узла
	free(lastNode);
	// Возвращение значения удалённого узла
	return lastValue;
}

// Удалить последний узел из списка с вершиной headNode
TBase PopBackList(ListNode **headNode)
{
	// Проверка на наличие узлов в списке
	if(headNode == NULL){ 
		return 0;
	}
	// Проверка на наличие одного узла в списке и его удаление
	if((*headNode)->p_nextNode == NULL){
		free(*headNode);
		*headNode = NULL;
		return 0;
	}
	// Нахождение указателя на предпоследний узел
	while((*headNode)->p_nextNode->p_nextNode != NULL){
		(*headNode) = (*headNode)->p_nextNode;
	}
	// Создание указателя на предпоследний узел
	ListNode *lastNode = (*headNode);
	TBase lastValue = lastNode->p_nextNode->value;
	// Удаление последнего узла
	free(lastNode->p_nextNode);
	lastNode->p_nextNode = NULL;
	// Возвращение значения удалённого узла
	return lastValue;
}


// Вставить узел со значением newValue в позицию index списка с вершиной headNode
void InsertList(ListNode *headNode, TCount index, TBase newValue)
{
	// Получение указателя на узел по индексу
	ListNode *prevNode = GetList(headNode, index);
	// Создание нового узла
	ListNode *newNode = (ListNode*) malloc(sizeof(ListNode));
	newNode->value = newValue;
	// Вставка узла в нужную позицию
	newNode->p_nextNode = prevNode->p_nextNode;
	prevNode->p_nextNode = newNode;
}

// Удалить index узел из списка с вершиной headNode
TBase RemoveList(ListNode **headNode, TCount index)
{
	// Проверка индекса (удаление первого элемента)
	if(index <= 0){
		return PopList(headNode);
	}
	// Получение указателя на узел перед искомым
	ListNode *prevNode = GetList(*headNode, index-1);
	// Если узлов нет, то выходим из функции
	if(prevNode == NULL){ 
		return 0;
	}
	// Создание указателя на удаляемый узел
	ListNode *delNode = prevNode->p_nextNode;
	prevNode->p_nextNode = delNode->p_nextNode;
	TBase lastValue = delNode->value;
	// Удаление узла
	free(delNode);
	// Возвращение значения удалённого узла
	return lastValue;
}


// Получить index узел из списка с вершиной headNode
ListNode *GetList(ListNode *headNode, TCount index)
{
	TCount cnt = 0;
	// Получение указателя на искомый узел
	while(cnt < index && headNode != NULL){
		headNode = headNode->p_nextNode;
		++cnt;
	}
	// Возвращение указателя на узел
	return headNode;
}

// Получить указатель на последний узел из списка с вершиной headNode
ListNode *GetLastList(ListNode *headNode)
{
	// Проверка на наличие узлов в списке
	if(headNode == NULL){ 
		return NULL;
	}
	// Нахождение последнего элемента
	while(headNode->p_nextNode != NULL){
		headNode = headNode->p_nextNode;
	}
	// Возвращение указателя на последний узел
	return headNode;
}

// Получить размер списка (кол-во узлов в нём)
TCount GetSizeList(ListNode *headNode)
{
	TCount sizeList = 0;
	// Подсчёт узлов до конца списка
	while(headNode != NULL){
		++sizeList;
		headNode = headNode->p_nextNode;
	}
	// Возвращение размера списка
	return sizeList;
}


// Вывод узлов списка с вершиной headNode
void PrintList(ListNode *headNode)
{
	TCount sizeList = GetSizeList(headNode);
	for(size_t index = 0 ; index < sizeList; index++){
		printf(FORMAT_COMMAND, GetList(headNode, index)->value);	// Вывод элемента
		putchar(DELIM_CHR);	// Вывод символа разделителя
	}
	putchar(CARR_CHR);	// Вывод символа перевода каретки
}

// Ввод узлов списка с вершиной headNode
ListNode *ScanList()
{
	TCount sizeList = 0;	// Размер списка
	// Ввод размера списка
	printf("Enter the number of nodes in the list: ");
	do{
		scanf("%d", &sizeList);
	}while(sizeList < 0 || MAX_LIST_SIZE < sizeList);
	
	TBase value = 0;
	printf("Enter the value [0] list node: ");
	scanf(FORMAT_COMMAND, &value);
	// Создание списка
	ListNode *headNode = InitList(value);
	// Заполнение списка
	for(size_t i = 1; i < sizeList; i++){
		printf("Enter the value [%ld] list node: ", i);
		scanf(FORMAT_COMMAND, &value);
		PushBackList(headNode, value);
	}
	// Возвращение указателя на готовый список
	return headNode;
}


// Создание линейного массива из элементов списка с вершиной headNode
TBase *ListToArray(ListNode *headNode, TCount *p_len)
{
	// Получение длины будущего массива (кол-ва узлов в списке)
	*p_len = GetSizeList(headNode);
	// Выделение памяти под массив
	TBase *arr = (TBase*) malloc((*p_len) * sizeof(TBase));
	// Заполнение массива
	for(size_t i = 0; i < *p_len; i++){
		// Получение значения из узла под индексом i
		arr[i] = GetList(headNode, i)->value;
	}
	// Возвращение указателя на массив
	return arr;
}

// Создание односвязного списка из массива arr с длиной len
ListNode *ArrayToList(TBase *arr, const TCount len)
{
	// Создание верщины списка
	ListNode *headNode = InitList(arr[0]);
	for(size_t i = 0; i < len; i++){
		// Создание узлов списка с элементами массива
		PushBackList(headNode, arr[i]);
	}
	// Возвращение указателя на вершину списка
	return headNode;
}
