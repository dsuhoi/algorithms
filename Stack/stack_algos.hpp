/*
 * stack_algos.hpp
 * 
 * Copyright 2020 DSuhoi
 * Библиотека для работы со стеком
 * (C++ library)
 */

#ifndef __STACK_LIB_HPP__
#define __STACK_LIB_HPP__

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
	// Деструктор
	~StackNode();
	
	
};


#endif
