/*
 * list_algos.hpp
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
#include "../Interface/data_interface.hpp"

//************
// Константы
//************
constexpr auto DELIM_CHR = ' ';       // символ разделитель


//***********************************************
// Константы для работы с односвязными списками
//***********************************************
constexpr auto MAX_LIST_SIZE = 1000;  // максимальное кол-во узлов в списке


//****************************
// Класс односвязного списка
//****************************

template <typename T>
class ListNode : public DataInterface<T> {
private:
	// Структура узла
	struct Node {
		// Указатель на следующий узел
		Node *p_nextNode;
		// Значение узла
		T value;
		// Конструкторы узла
		Node() : p_nextNode(nullptr) {}
		Node(T newValue) : value(newValue), p_nextNode(nullptr) {}
	};
	// Вершина списка
	Node *m_headNode;

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
		T operator *();
		// Оператор инкрементирования
		void operator ++();
	};

	ListNode(); // Пустой конструктор
	// Конструктор списка по numNode количеству узлов в нём (все узлы равны 0)
	ListNode(const unsigned int numNode);
	// Конструктор списка по numNode количеству узлов в нём
	// (все узлы равны случайным числам с пределом randomRange)
	ListNode(const unsigned int numNode, const unsigned int randomRange = 1000);
	// Деструктор списка
	~ListNode();

	// Добавить newValue узел в начало списка
	void push(T newValue) override;
	// Добавить newValue узел в конец списка
	void pushBack(T newValue) override;

	// Удалить первый узел
	T pop() override;
	// Удалить последний узел
	T popBack() override;

	// Вставить newValue узел в позицию index
	void insert(T newValue, const unsigned int index);

	// Получить значение узла в позиции index
	T getNode(const unsigned int index);
	// Получить количество узлов в списке
	size_t size() override;

	// Вывод всех элементов списка
	void print() override;
	// Ввод элементов списка
	void scan() override;

	friend std::ofstream &operator<<(std::ofstream &out, ListNode<T> &list);

	// Возвращение итератора начала списка
	ListIterator begin();
	// Возвращение итератора конца списка
	ListIterator end();

	// Создание массива (со ссылкой на длину arrayLen) из элементов списка
	T *listToArray(unsigned int &arrayLen);
};

//***********************************************
// Функции класса итератора односвязного списка
//***********************************************
// Конструктор класса
template <typename T>
ListNode<T>::ListIterator::ListIterator(Node *_node) : currentNode(_node) {}

// Операторы сравнения
template <typename T>
bool ListNode<T>::ListIterator::operator ==(const ListIterator &iter)
{
	if (this == &iter)
		return true;
	else
		return currentNode == iter.currentNode;
}

template <typename T>
bool ListNode<T>::ListIterator::operator !=(const ListIterator &iter)
{
	return !(this == iter);
}

// Оператор разыменования
template <typename T>
T ListNode<T>::ListIterator::operator *()
{
	if (currentNode != nullptr)
		return currentNode->value;
	else
		return T();
}

// Оператор инкрементирования
template <typename T>
void ListNode<T>::ListIterator::operator ++()
{
	if (currentNode != nullptr)
		currentNode = currentNode->p_nextNode;
}

// Возвращение итератора начала списка
template <typename T>
typename ListNode<T>::ListIterator ListNode<T>::begin()
{
	return ListIterator(m_headNode);
}

// Возвращение итератора конца списка
template <typename T>
typename ListNode<T>::ListIterator ListNode<T>::end()
{
	return ListIterator(nullptr);
}

//*************************************
// Функции класса односвязного списка
//*************************************
// Пустой конструктор
template <typename T>
ListNode<T>::ListNode() : m_headNode(nullptr) {}

// Конструктор списка с numNode узлами
template <typename T>
ListNode<T>::ListNode(const unsigned int numNode) : m_headNode(nullptr)
{
	for (size_t i = 0; i < numNode; ++i)
		push(0);
}

// Конструктор списка по numNode количеству узлов в нём
// (все узлы равны случайным числам с пределом randomRange)
template <typename T>
ListNode<T>::ListNode(const unsigned int numNode, const unsigned int randomRange) : m_headNode(nullptr)
{
	srand(time(NULL));

	for (size_t i = 0; i < numNode; ++i)
		push(rand() % randomRange);
}

// Деструктор списка
template <typename T>
ListNode<T>::~ListNode()
{
	while (m_headNode != nullptr)
		pop();
}


// Добавить newValue узел в начало списка
template <typename T>
void ListNode<T>::push(T newValue)
{
	// Выделение памяти под новый узел
	if (Node *newNode = new Node(newValue)) {
		// Смена указателя на верхний узел
		newNode->p_nextNode = m_headNode;
		// Перестановка указателя на новый верхний узел
		m_headNode = newNode;
	}
}

// Добавить newValue узел в конец списка
template <typename T>
void ListNode<T>::pushBack(T newValue)
{
	// Выделение памяти под первый узел и присвоение значений
	if (Node *newNode = new Node(newValue)) {
		newNode->p_nextNode = nullptr;
		// Получение указателя на последний узел
		ListNode *lastNode = m_headNode;
		// Нахождение последнего элемента списка
		while (lastNode->p_nextNode!=nullptr)
			lastNode = lastNode->p_nextNode;
		// Присвоение указателя
		lastNode->p_nextNode = newNode;
	}
}


// Удалить первый узел
template <typename T>
T ListNode<T>::pop()
{
	// Проверка на наличие узлов в списке
	if (m_headNode == nullptr)
		return T();
	// Создание указателя на вершину списка
	ListNode *lastNode = m_headNode;
	T lastValue = lastNode->value;
	m_headNode = m_headNode->p_nextNode;
	// Удаление узла
	free(lastNode);
	// Возвращение значения удалённого узла
	return lastValue;
}

// Удалить последний узел
template <typename T>
T ListNode<T>::popBack()
{
	// Проверка на наличие узлов в списке
	if (m_headNode == nullptr)
		return T();
	// Проверка на наличие одного узла в списке и его удаление
	if (m_headNode->p_nextNode == nullptr) {
		free(m_headNode);
		m_headNode = nullptr;
		return T();
	}
	// Нахождение указателя на предпоследний узел
	while (m_headNode->p_nextNode->p_nextNode != nullptr)
		m_headNode = m_headNode->p_nextNode;
	// Создание указателя на предпоследний узел
	ListNode *lastNode = m_headNode;
	// Значение последнего узла
	T lastValue = lastNode->p_nextNode->value;
	// Удаление последнего узла
	free(lastNode->p_nextNode);
	// Установка нулевого указателя
	lastNode->p_nextNode = nullptr;
	// Возвращение значения удалённого узла
	return lastValue;
}

// Вставить newValue узел в позицию index
template <typename T>
void ListNode<T>::insert(T newValue, const unsigned int index)
{
	// Получение указателя на узел до индекса
	ListNode *prevNode = m_headNode;
	size_t cnt = 0;
	while (cnt < index && prevNode != nullptr) {
		prevNode = prevNode->p_nextNode;
		++cnt;
	}

	// Создание нового узла
	if (ListNode *newNode = new ListNode(newValue)) {
		// Вставка узла в нужную позицию
		newNode->p_nextNode = prevNode->p_nextNode;
		prevNode->p_nextNode = newNode;
	}
}

// Получить значение узла в позиции index
template <typename T>
T ListNode<T>::getNode(const unsigned int index)
{
	// Создание указателя на узел
	ListNode *indexNode = m_headNode;
	size_t cnt = 0;
	// Получение указателя на искомый узел
	while ((cnt++) < index && indexNode != nullptr)
		indexNode = indexNode->p_nextNode;
	// Возвращение значения узла
	return indexNode->value;
}


// Вывод всех элементов списка
template <typename T>
void ListNode<T>::print()
{
	// Получение размера списка
	unsigned int listSize = size();
	for (size_t index = 0 ; index < listSize; ++index)
		// Вывод элемента и символа разделителя
		std::cout << getNode(index) << DELIM_CHR;
	std::cout << std::endl; // Вывод символа перевода каретки
}

// Ввод элементов списка
template <typename T>
void ListNode<T>::scan()
{
	unsigned int sizeList = 0;  // Размер списка
	// Ввод размера списка
	std::cout << "Enter the number of nodes in the list: ";
	do {
		std::cin >> sizeList;
	} while (sizeList < 0 || MAX_LIST_SIZE < sizeList);

	T value = 0;
	std::cout << "Enter the value [0] list node: ";
	std::cin >> value;
	// Первый узел списка
	PushBack(value);
	// Заполнение списка
	for (size_t i = 1; i < sizeList; ++i) {
		std::cout << "Enter the value [" << i << "] list node: ";
		std::cin >> value;
		PushBackList(value);
	}
}

// Получить количество узлов в списке
template <typename T>
size_t ListNode<T>::size()
{
	size_t sizeList = 0;
	ListNode *listCounter = m_headNode;
	// Подсчёт узлов до конца списка
	while (listCounter != nullptr) {
		++sizeList;
		listCounter = listCounter->p_nextNode;
	}
	// Возвращение размера списка
	return sizeList;
}

// Создание массива (со ссылкой на длину ArrayLen) из элементов списка с вершиной m_headNode
template <typename T>
T *ListNode<T>::listToArray(unsigned int &arrayLen)
{
	// Получение длины будущего массива (кол-ва узлов в списке)
	arrayLen = size();
	// Выделение памяти под массив
	T *arr = new T[arrayLen];
	// Заполнение массива
	for (size_t i = 0; i < arrayLen; ++i)
		// Получение значения из узла под индексом i
		arr[i] = GetList(m_headNode, i)->value;
	// Возвращение указателя на массив
	return arr;
}

#endif
