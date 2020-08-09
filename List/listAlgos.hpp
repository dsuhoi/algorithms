/*
 * listAlgos.hpp
 * 
 * Copyright 2020 DSuhoi
 * 
 * Библиотека класса односвязного списка.
 * Методы ввода, вывода, заполнения, поиска и т.п.
 * (C++ library)
 */

#ifndef __LIST_LIB_HPP__
#define __LIST_LIB_HPP__

#include <iostream>
#include <ctime>


//*********************************
// Основные константы
//*********************************
#define DELIM_CHR ' '	// символ разделитель


//********************************************************
// Основные константы для работы с односвязными списками
//********************************************************
#define MAX_LIST_SIZE 1000	// максимальное кол-во узлов в списке


//****************************
// Класс односвязного списка
//****************************

template <typename TBase>
class ListNode {
private:
	// Структура узла
	struct Node {
		Node *p_nextNode;
		TBase value;
		// Конструкторы узла
		Node() : p_nextNode(nullptr) {}
		Node(TBase newValue) : value(newValue), p_nextNode(nullptr) {}
	};
	// Вершина списка
	Node *headNode;

	// Получить указатель на последний узел
	Node *GetLastNode();
public:
	ListNode();	// Пустой конструктор
	// Конструктор списка по numNode количеству узлов в нём (все узлы равны 0)
	ListNode(const unsigned int numNode);
	// Конструктор списка по numNode количеству узлов в нём
	// (все узлы равны случайным числам с пределом randomRange)
	ListNode(const unsigned int numNode, const unsigned int randomRange = 1000);
	// Деструктор списка
	~ListNode();
	
	// Добавить newValue узел в начало списка
	void Push(TBase newValue);
	// Добавить newValue узел в конец списка
	void PushBack(TBase newValue);
	
	// Удалить первый узел
	TBase Pop();
	// Удалить последний узел
	TBase PopBack();
	
	// Вставить newValue узел в позицию index
	void Insert(TBase newValue, const unsigned int index);
	
	// Получить значение узла в позиции index
	TBase GetNode(const unsigned int index);
	// Получить значение последнего узла
	TBase GetLast();
	// Получить количество узлов в списке
	unsigned int GetSize();
	
	// Вывод всех элементов списка
	void Print();
	// Ввод элементов списка
	void Scan();
};


//*********************************************
// Основные методы класса односвязного списка
//*********************************************
// Пустой конструктор
template <typename TBase>
ListNode<TBase>::ListNode() : headNode(nullptr) {}

// Конструктор списка с numNode узлами
template <typename TBase>
ListNode<TBase>::ListNode(const unsigned int numNode) : headNode(nullptr)
{
	for(size_t i = 0; i < numNode; i++){
		Push(0);
	}
}

// Конструктор списка по numNode количеству узлов в нём
// (все узлы равны случайным числам с пределом randomRange)
template <typename TBase>
ListNode<TBase>::ListNode(const unsigned int numNode, const unsigned int randomRange) : headNode(nullptr)
{
	srand(time(NULL));
	
	for(size_t i = 0; i < numNode; i++){
		Push(rand() % randomRange);
	}
}

// Деструктор списка
template <typename TBase>
ListNode<TBase>::~ListNode()
{
	while(Pop()!=NULL);
}


// Добавить newValue узел в начало списка
template <typename TBase>
void ListNode<TBase>::Push(TBase newValue)
{
	// Выделение памяти под новый узел
	if(Node *newNode = new Node(newValue)){
		// Смена указателя на верхний узел
		newNode->p_nextNode = headNode;
		// Перестановка указателя на новый верхний узел
		headNode = newNode;
	}
}

// Добавить newValue узел в конец списка
template <typename TBase>
void ListNode<TBase>::PushBack(TBase newValue)
{
	// Выделение памяти под первый узел и присвоение значений
	if(Node *newNode = new Node(newValue)){
		newNode->p_nextNode = nullptr;
		// Получение указателя на последний узел
		ListNode *lastNode = headNode;
		// Нахождение последнего элемента списка
		while(lastNode->p_nextNode!=nullptr){
			lastNode = lastNode->p_nextNode;
		}
		// Присвоение указателя
		lastNode->p_nextNode = newNode;
	}
}


// Удалить первый узел
template <typename TBase>
TBase ListNode<TBase>::Pop()
{
	// Проверка на наличие узлов в списке
	if(headNode == nullptr) return NULL;
	// Создание указателя на вершину списка
	ListNode *lastNode = headNode;
	TBase lastValue = lastNode->value;
	headNode = headNode->p_nextNode;
	// Удаление узла
	free(lastNode);
	// Возвращение значения удалённого узла
	return lastValue;
}

// Удалить последний узел
template <typename TBase>
TBase ListNode<TBase>::PopBack()
{
	// Проверка на наличие узлов в списке
	if(headNode==nullptr) return NULL;
	// Проверка на наличие одного узла в списке и его удаление
	if(headNode->p_nextNode == nullptr){
		free(headNode);
		headNode = nullptr;
		return NULL;
	}
	// Нахождение указателя на предпоследний узел
	while(headNode->p_nextNode->p_nextNode != nullptr){
		headNode = headNode->p_nextNode;
	}
	// Создание указателя на предпоследний узел
	ListNode *lastNode = headNode;
	// Значение последнего узла
	TBase lastValue = lastNode->p_nextNode->value;
	// Удаление последнего узла
	free(lastNode->p_nextNode);
	// Установка нулевого указателя
	lastNode->p_nextNode = nullptr;
	// Возвращение значения удалённого узла
	return lastValue;
}

// Вставить newValue узел в позицию index
template <typename TBase>
void ListNode<TBase>::Insert(TBase newValue, const unsigned int index)
{
	// Получение указателя на узел до индекса
	ListNode *prevNode = headNode;
	size_t cnt = 0;
	while(cnt < index && prevNode!=nullptr){
		prevNode = prevNode->p_nextNode;
		++cnt;
	}
	
	// Создание нового узла
	if(ListNode *newNode = new ListNode(newValue)){
		// Вставка узла в нужную позицию
		newNode->p_nextNode = prevNode->p_nextNode;
		prevNode->p_nextNode = newNode;
	}
}


#endif
