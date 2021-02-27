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
#include "../interface/data_interface.hpp"

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
class List_node : public Data_interface<T>
{
private:
	// Структура узла
	struct Node {
		// Указатель на следующий узел
		Node *p_next_node;
		// Значение узла
		T value;
		// Конструкторы узла
		Node() : p_next_node(nullptr) {}
		Node(T new_value) : value(new_value), p_next_node(nullptr) {}
	};
	// Вершина списка
	Node *m_head_node;

public:
	// Класс итератора односвязного списка
	class List_iterator {
	private:
		Node *current_node;
	public:
		// Конструктор класса
		List_iterator(Node *_node);
		// Операторы сравнения
		bool operator ==(const List_iterator &iter);
		bool operator !=(const List_iterator &iter);
		// Оператор разыменования
		T operator *();
		// Оператор инкрементирования
		void operator ++();
	};

	List_node(); // Пустой конструктор
	// Конструктор списка по num_node количеству узлов в нём (все узлы равны 0)
	List_node(const unsigned int num_node);
	// Конструктор списка по num_node количеству узлов в нём
	// (все узлы равны случайным числам с пределом random_range)
	List_node(const unsigned int num_node, const unsigned int random_range = 1000);
	// Деструктор списка
	~List_node();

	// Добавить new_value узел в начало списка
	void push(T new_value) override;
	// Добавить new_value узел в конец списка
	void push_back(T new_value) override;

	// Удалить первый узел
	T pop() override;
	// Удалить последний узел
	T pop_back() override;

	// Вставить new_value узел в позицию index
	void insert(T new_value, const unsigned int index);

	// Получить значение узла в позиции index
	T get_node(const unsigned int index);
	// Получить количество узлов в списке
	size_t size() override;

	// Вывод всех элементов списка
	void print() override;
	// Ввод элементов списка
	void scan() override;

	friend std::ofstream &operator<<(std::ofstream &out, List_node<T> &list);

	// Возвращение итератора начала списка
	List_iterator begin();
	// Возвращение итератора конца списка
	List_iterator end();

	// Создание массива (со ссылкой на длину arrayLen) из элементов списка
	T *list_to_array(unsigned int &array_len);
};

//***********************************************
// Функции класса итератора односвязного списка
//***********************************************
// Конструктор класса
template <typename T>
List_node<T>::List_iterator::List_iterator(Node *_node) : current_node(_node) {}

// Операторы сравнения
template <typename T>
bool List_node<T>::List_iterator::operator ==(const List_iterator &iter)
{
	if (this == &iter)
		return true;
	else
		return current_node == iter.current_node;
}

template <typename T>
bool List_node<T>::List_iterator::operator !=(const List_iterator &iter)
{
	return !(this == iter);
}

// Оператор разыменования
template <typename T>
T List_node<T>::List_iterator::operator *()
{
	if (current_node != nullptr)
		return current_node->value;
	else
		return T();
}

// Оператор инкрементирования
template <typename T>
void List_node<T>::List_iterator::operator ++()
{
	if (current_node != nullptr)
		current_node = current_node->p_next_node;
}

// Возвращение итератора начала списка
template <typename T>
typename List_node<T>::List_iterator List_node<T>::begin()
{
	return List_iterator(m_head_node);
}

// Возвращение итератора конца списка
template <typename T>
typename List_node<T>::List_iterator List_node<T>::end()
{
	return List_iterator(nullptr);
}

//*************************************
// Функции класса односвязного списка
//*************************************
// Пустой конструктор
template <typename T>
List_node<T>::List_node() : m_head_node(nullptr) {}

// Конструктор списка с num_node узлами
template <typename T>
List_node<T>::List_node(const unsigned int num_node) : m_head_node(nullptr)
{
	for (size_t i = 0; i < num_node; ++i)
		push(0);
}

// Конструктор списка по num_node количеству узлов в нём
// (все узлы равны случайным числам с пределом random_range)
template <typename T>
List_node<T>::List_node(const unsigned int num_node, const unsigned int random_range) : m_head_node(nullptr)
{
	srand(time(NULL));

	for (size_t i = 0; i < num_node; ++i)
		push(rand() % random_range);
}

// Деструктор списка
template <typename T>
List_node<T>::~List_node()
{
	while (m_head_node != nullptr)
		pop();
}


// Добавить new_value узел в начало списка
template <typename T>
void List_node<T>::push(T new_value)
{
	// Выделение памяти под новый узел
	if (Node *new_node = new Node(new_value)) {
		// Смена указателя на верхний узел
		new_node->p_next_node = m_head_node;
		// Перестановка указателя на новый верхний узел
		m_head_node = new_node;
	}
}

// Добавить new_value узел в конец списка
template <typename T>
void List_node<T>::push_back(T new_value)
{
	// Выделение памяти под первый узел и присвоение значений
	if (Node *new_node = new Node(new_value)) {
		new_node->p_next_node = nullptr;
		// Получение указателя на последний узел
		List_node *lastNode = m_head_node;
		// Нахождение последнего элемента списка
		while (lastNode->p_next_node!=nullptr)
			lastNode = lastNode->p_next_node;
		// Присвоение указателя
		lastNode->p_next_node = new_node;
	}
}


// Удалить первый узел
template <typename T>
T List_node<T>::pop()
{
	// Проверка на наличие узлов в списке
	if (m_head_node == nullptr)
		return T();
	// Создание указателя на вершину списка
	List_node *lastNode = m_head_node;
	T lastValue = lastNode->value;
	m_head_node = m_head_node->p_next_node;
	// Удаление узла
	free(lastNode);
	// Возвращение значения удалённого узла
	return lastValue;
}

// Удалить последний узел
template <typename T>
T List_node<T>::pop_back()
{
	// Проверка на наличие узлов в списке
	if (m_head_node == nullptr)
		return T();
	// Проверка на наличие одного узла в списке и его удаление
	if (m_head_node->p_next_node == nullptr) {
		free(m_head_node);
		m_head_node = nullptr;
		return T();
	}
	// Нахождение указателя на предпоследний узел
	while (m_head_node->p_next_node->p_next_node != nullptr)
		m_head_node = m_head_node->p_next_node;
	// Создание указателя на предпоследний узел
	List_node *lastNode = m_head_node;
	// Значение последнего узла
	T lastValue = lastNode->p_next_node->value;
	// Удаление последнего узла
	free(lastNode->p_next_node);
	// Установка нулевого указателя
	lastNode->p_next_node = nullptr;
	// Возвращение значения удалённого узла
	return lastValue;
}

// Вставить new_value узел в позицию index
template <typename T>
void List_node<T>::insert(T new_value, const unsigned int index)
{
	// Получение указателя на узел до индекса
	List_node *prev_node = m_head_node;
	size_t cnt = 0;
	while (cnt < index && prev_node != nullptr) {
		prev_node = prev_node->p_next_node;
		++cnt;
	}

	// Создание нового узла
	if (List_node *new_node = new List_node(new_value)) {
		// Вставка узла в нужную позицию
		new_node->p_next_node = prev_node->p_next_node;
		prev_node->p_next_node = new_node;
	}
}

// Получить значение узла в позиции index
template <typename T>
T List_node<T>::get_node(const unsigned int index)
{
	// Создание указателя на узел
	List_node *index_node = m_head_node;
	size_t cnt = 0;
	// Получение указателя на искомый узел
	while ((cnt++) < index && index_node != nullptr)
		index_node = index_node->p_next_node;
	// Возвращение значения узла
	return index_node->value;
}


// Вывод всех элементов списка
template <typename T>
void List_node<T>::print()
{
	// Получение размера списка
	unsigned int list_size = size();
	for (size_t index = 0 ; index < list_size; ++index)
		// Вывод элемента и символа разделителя
		std::cout << get_node(index) << DELIM_CHR;
	std::cout << std::endl; // Вывод символа перевода каретки
}

// Ввод элементов списка
template <typename T>
void List_node<T>::scan()
{
	unsigned int size_list = 0;  // Размер списка
	// Ввод размера списка
	std::cout << "Enter the number of nodes in the list: ";
	do {
		std::cin >> size_list;
	} while (size_list < 0 || MAX_LIST_SIZE < size_list);

	T value = 0;
	std::cout << "Enter the value [0] list node: ";
	std::cin >> value;
	// Первый узел списка
	push_back(value);
	// Заполнение списка
	for (size_t i = 1; i < size_list; ++i) {
		std::cout << "Enter the value [" << i << "] list node: ";
		std::cin >> value;
		push_back(value);
	}
}

// Получить количество узлов в списке
template <typename T>
size_t List_node<T>::size()
{
	size_t size_list = 0;
	List_node *list_counter = m_head_node;
	// Подсчёт узлов до конца списка
	while (list_counter != nullptr) {
		++size_list;
		list_counter = list_counter->p_next_node;
	}
	// Возвращение размера списка
	return size_list;
}

// Создание массива (со ссылкой на длину ArrayLen) из элементов списка с вершиной m_head_node
template <typename T>
T *List_node<T>::list_to_array(unsigned int &array_len)
{
	// Получение длины будущего массива (кол-ва узлов в списке)
	array_len = size();
	// Выделение памяти под массив
	T *arr = new T[array_len];
	// Заполнение массива
	for (size_t i = 0; i < array_len; ++i)
		// Получение значения из узла под индексом i
		arr[i] = GetList(m_head_node, i)->value;
	// Возвращение указателя на массив
	return arr;
}

#endif
