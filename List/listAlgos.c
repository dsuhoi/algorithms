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
