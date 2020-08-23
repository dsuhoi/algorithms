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
		// Указатель на следующий узел
		Node *p_nextNode;
		// Значение узла
		TBase value;
		// Конструкторы узла
		Node() : p_nextNode(nullptr) {}
		Node(TBase newValue) : value(newValue), p_nextNode(nullptr) {}
	};
	// Вершина списка
	Node *headNode;

public:
	// Класс итератора односвязного списка
	class ListIterator {
	private:
		Node *currentNode;
	public:
		// Конструктор класса
		ListIterator(Node *_node);
		// Операторы сравнения
		bool operator ==(const ListIterator &iter);
		bool operator !=(const ListIterator &iter);
		// Оператор разыменования
		TBase operator *();
		// Оператор инкрементирования
		void operator ++();
	};



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
	// Получить количество узлов в списке
	unsigned int GetSize();
	
	// Вывод всех элементов списка
	void Print();
	// Ввод элементов списка
	void Scan();
	
	// Возвращение итератора начала списка
	ListIterator Begin();
	// Возвращение итератора конца списка
	ListIterator End();
	
	// Создание массива (со ссылкой на длину ArrayLen) из элементов списка
	TBase *ListToArray(unsigned int &ArrayLen);
};

//*******************************************************
// Основные методы класса итератора односвязного списка
//*******************************************************
// Конструктор класса
template <typename TBase>
ListNode<TBase>::ListIterator::ListIterator(Node *_node) : currentNode(_node) {}

// Операторы сравнения
template <typename TBase>
bool ListNode<TBase>::ListIterator::operator ==(const ListIterator &iter)
{
	if(this == &iter){
		return true;
	}
	return currentNode == iter.currentNode;
}

template <typename TBase>
bool ListNode<TBase>::ListIterator::operator !=(const ListIterator &iter)
{
	return !(this == iter);
}


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
	if(headNode == nullptr){ 
		return NULL;
	}
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
	if(headNode==nullptr){ 
		return NULL;
	}
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

// Получить значение узла в позиции index
template <typename TBase>
TBase ListNode<TBase>::GetNode(const unsigned int index)
{
	// Создание указателя на узел
	ListNode *indexNode = headNode;
	size_t cnt = 0;
	// Получение указателя на искомый узел
	while(cnt < index && indexNode != NULL){
		indexNode = indexNode->p_nextNode;
		++cnt;
	}
	// Возвращение значения узла
	return indexNode->value;
}


// Вывод всех элементов списка
template <typename TBase>
void ListNode<TBase>::Print()
{
	// Получение размера списка
	unsigned int listSize = GetSize();
	for(size_t index = 0 ; index < listSize; index++){
		// Вывод элемента и символа разделителя
		std::cout << GetNode(index) << DELIM_CHR;
	}
	std::cout << std::endl;	// Вывод символа перевода каретки
}

// Ввод элементов списка
template <typename TBase>
void ListNode<TBase>::Scan()
{
	unsigned int sizeList = 0;	// Размер списка
	// Ввод размера списка
	std::cout << "Enter the number of nodes in the list: ";
	do{
		std::cin >> sizeList;
	}while(sizeList < 0 || MAX_LIST_SIZE < sizeList);
	
	TBase value = 0;
	std::cout << "Enter the value [0] list node: ";
	std::cin >> value;
	// Первый узел списка
	PushBack(value);
	// Заполнение списка
	for(size_t i = 1; i < sizeList; i++){
		std::cout << "Enter the value [" << i << "] list node: ";
		std::cin >> value;
		PushBackList(value);
	}
}

// Получить количество узлов в списке
template <typename TBase>
unsigned int ListNode<TBase>::GetSize()
{
	unsigned int sizeList = 0;
	ListNode *listCounter = headNode;
	// Подсчёт узлов до конца списка
	while(listCounter != NULL){
		++sizeList;
		listCounter = listCounter->p_nextNode;
	}
	// Возвращение размера списка
	return sizeList;
}

// Создание массива (со ссылкой на длину ArrayLen) из элементов списка с вершиной headNode
template <typename TBase>
TBase *ListNode<TBase>::ListToArray(unsigned int &ArrayLen)
{
	// Получение длины будущего массива (кол-ва узлов в списке)
	ArrayLen = GetSize();
	// Выделение памяти под массив
	TBase *arr = (TBase*) malloc(ArrayLen * sizeof(TBase));
	// Заполнение массива
	for(size_t i = 0; i < ArrayLen; i++){
		// Получение значения из узла под индексом i
		arr[i] = GetList(headNode, i)->value;
	}
	// Возвращение указателя на массив
	return arr;
}

#endif
