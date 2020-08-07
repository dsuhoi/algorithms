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


//****************************
// Класс односвязного списка
//****************************

template <typename TBase>
class ListNode {
private:
	// Структура узла
	struct Node {
		Node* p_nextNode;
		TBase value;
		// Конструкторы узла
		Node() : p_nextNode(nullptr) {}
		Node(TBase newValue) : value(newValue), p_nextNode(nullptr) {}
	};
	// Вершина списка
	Node* headNode;
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
	
	// Вывод всех элементов списка
	void Print();
	// Ввод элементов списка
	void Scan();
	
	// Получить количество узлов в списке
	unsigned int GetSize();
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



#endif
