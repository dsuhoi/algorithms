#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "listAlgos.h"


//*****************************************************
// Основные функции по работе с односвязными списками
//*****************************************************

// Создание списка и его первого узла
Node* InitList(TBase newValue)
{
	// Выделение памяти под первый узел и присвоение значений
	Node* headNode = (Node*) malloc(sizeof(Node));
	headNode->value = newValue;
	return headNode;
}


// Вставить узел со значением newValue в начало списка с вершиной headNode
void PushList(Node** headNode, TBase newValue)
{
	// Выделение памяти под первый узел и присвоение значений
	Node* newNode = (Node*) malloc(sizeof(Node));
	newNode->value = newValue;
	// Смена указателя на верхний узел
	newNode->p_nextNode = (*headNode);
	// Перестановка указателя на новый верхний узел
	(*headNode) = newNode;
}

// Вставить узел со значением newValue в конец списка с вершиной headNode
void PushBackList(Node* headNode, TBase newValue)
{
	// Выделение памяти под первый узел и присвоение значений
	Node* newNode = (Node*) malloc(sizeof(Node));
	newNode->value = newValue;
	newNode->p_nextNode = NULL;
	// Получение указателя на последний узел
	Node* lastNode = GetLastList(headNode);
	lastNode->p_nextNode = newNode;
}


// Удалить начальный узел из списка с вершиной headNode
TBase PopList(Node** headNode)
{
	// Проверка на наличие узлов в списке
	if(headNode==NULL) return 0;
	// Создание указателя на вершину списка
	Node* lastNode = (*headNode);
	TBase lastValue = lastNode->value;
	(*headNode) = (*headNode)->p_nextNode;
	// Удаление узла
	free(lastNode);
	// Возвращение значения удалённого узла
	return lastValue;
}

// Удалить последний узел из списка с вершиной headNode
TBase PopBackList(Node** headNode)
{
	// Проверка на наличие узлов в списке
	if(headNode==NULL) return 0;
	// Проверка на наличие одного узла в списке и его удаление
	if((*headNode)->p_nextNode==NULL){
		free(*headNode);
		*headNode = NULL;
		return 0;
	}
	// Нахождение указателя на предпоследний узел
	while((*headNode)->p_nextNode->p_nextNode!=NULL){
		(*headNode) = (*headNode)->p_nextNode;
	}
	// Создание указателя на предпоследний узел
	Node* lastNode = (*headNode);
	TBase lastValue = lastNode->p_nextNode->value;
	// Удаление последнего узла
	free(lastNode->p_nextNode);
	lastNode->p_nextNode = NULL;
	// Возвращение значения удалённого узла
	return lastValue;
}


// Вставить узел со значением newValue в позицию index списка с вершиной headNode
void InsertList(Node* headNode, TCount index, TBase newValue)
{
	// Получение указателя на узел по индексу
	Node* prevNode = GetList(headNode, index);
	// Создание нового узла
	Node* newNode = (Node*) malloc(sizeof(Node));
	newNode->value = newValue;
	// Вставка узла в нужную позицию
	newNode->p_nextNode = prevNode->p_nextNode;
	prevNode->p_nextNode = newNode;
}

// Удалить index узел из списка с вершиной headNode
TBase RemoveList(Node** headNode, TCount index)
{
	// Проверка индекса (удаление первого элемента)
	if(index<=0){
		return PopList(headNode);
	}
	// Получение указателя на узел перед искомым
	Node* prevNode = GetList(*headNode, index-1);
	// Если узлов нет, то выходим из функции
	if(prevNode==NULL) return 0;
	// Создание указателя на удаляемый узел
	Node* delNode = prevNode->p_nextNode;
	prevNode->p_nextNode = delNode->p_nextNode;
	TBase lastValue = delNode->value;
	// Удаление узла
	free(delNode);
	// Возвращение значения удалённого узла
	return lastValue;
}


// Получить index узел из списка с вершиной headNode
Node* GetList(Node* headNode, TCount index)
{
	TCount cnt = 0;
	// Получение указателя на искомый узел
	while(cnt < index && headNode!=NULL){
		headNode = headNode->p_nextNode;
		++cnt;
	}
	// Возвращение указателя на узел
	return headNode;
}

// Получить указатель на последний узел из списка с вершиной headNode
Node* GetLastList(Node* headNode)
{
	// Проверка на наличие узлов в списке
	if(headNode == NULL) return NULL;
	// Нахождение последнего элемента
	while(headNode->p_nextNode!=NULL){
		headNode = headNode->p_nextNode;
	}
	// Возвращение указателя на последний узел
	return headNode;
}

// Получить размер списка (кол-во узлов в нём)
TCount GetSizeList(Node* headNode)
{
	TCount sizeList = 0;
	// Подсчёт узлов до конца списка
	while(headNode!=NULL){
		++sizeList;
		headNode = headNode->p_nextNode;
	}
	// Возвращение размера списка
	return sizeList;
}


// Вывод узлов списка с вершиной headNode
void ListPrint(Node* headNode)
{
	TCount sizeList = GetSizeList(headNode);
	for(size_t i = 0 ; i<sizeList; i++){
		printf(FORMAT_COMMAND, GetList(headNode, i)->value);	// Вывод элемента
		putchar(DELIM_CHR);	// Вывод символа разделителя
	}
	putchar(CARR_CHR);	// Вывод символа перевода каретки
}
