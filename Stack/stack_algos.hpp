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
	// Вернуть значение последнего элемента
	TBase Top();
	
	// Очистка всего стека
	void Clear();
	// Вернуть размер стека
	unsigned int Size();
	
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
	Clear();
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

// Удаление элемента из стека
template <typename TBase>
TBase StackNode<TBase>::Pop()
{
	// Проверка последнего элемента
	if(endNode == nullptr){
		return TBase();
	}
	
	Node *removeNode = endNode;
	endNode = endNode->p_lastNode;
	TBase value = removeNode->value;
	// Удаление последнего элемента
	delete removeNode;
	// Возвращение значения элемента стека
	return value;
}

// Вернуть значение последнего элемента
template <typename TBase>
TBase StackNode<TBase>::Top()
{
	if(endNode == nullptr){
		return TBase();
	}
	
	return endNode->value;
}

// Очистка всего стека
template <typename TBase>
void StackNode<TBase>::Clear()
{
	while(endNode != nullptr){
		Pop();
	}
}

// Вернуть размер стека!
template <typename TBase>
unsigned int StackNode<TBase>::Size()
{
	Node *lastNode = endNode;
	unsigned int size = 0;
	// Подсчёт элементов
	while(lastNode != nullptr){
		lastNode = lastNode->p_lastNode;
		++size;
	}
	// Возвращение размера стека
	return size;
}

#endif
