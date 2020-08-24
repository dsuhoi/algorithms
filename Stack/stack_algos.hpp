/*
 * stack_algos.hpp
 * 
 * Copyright 2020 DSuhoi
 * Библиотека для работы со стеком
 * (C++ library)
 */

#ifndef __STACK_LIB_HPP__
#define __STACK_LIB_HPP__



//**************
// Класс стека
//**************
template <typename TBase>
class StackNode {
private:
	// Структура элементов стека
	struct Node {
		// Указатель на прошлый элемент
		Node *p_lastNode;
		// Значение элемента стека
		TBase value;
		// Конструкторы
		Node() : p_lastNode(nullptr) {}
		Node(TBase newValue) : value(newValue), p_lastNode(nullptr) {}
	};
	
	// Конец стека
	Node *endNode;
public:
	// Конструктор
	StackNode();
	// Конструктор с параметром
	StackNode(TBase newValue);
	// Деструктор
	~StackNode();
	// Создание нового элемента стека
	void Push(TBase newValue);
	// Удаление элемента из стека
	TBase Pop();
	
};

//********************************
// Основные функции класса стека
//********************************

// Конструктор
template <typename TBase>
StackNode<TBase>::StackNode() : endNode(nullptr) {}

// Конструктор с параметром
template <typename TBase>
StackNode<TBase>::StackNode(TBase newValue)
{
	endNode = new Node(newValue);
}

// Деструктор
template <typename TBase>
StackNode<TBase>::~StackNode()
{
	while(endNode != nullptr){
		Pop();
	}
}

// Создание нового элемента стека
template <typename TBase>
void StackNode<TBase>::Push(TBase newValue)
{
	Node *newNode;
	if(newNode = new Node(newValue)){
		newNode->p_lastNode = endNode;
		endNode = newNode;
	}
}

#endif
