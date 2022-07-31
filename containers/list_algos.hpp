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

#include <cstddef>
#include <iostream>

#include "data_interface.hpp"

//****************************
// Класс односвязного списка
//****************************

template <typename T, auto MAX_LIST_SIZE = 1000, auto DELIM_CHR = ' '>
class List_node : public Data_interface<T>
{
    // Структура узла
    struct Node
    {
        // Указатель на следующий узел
        Node* p_next_node;
        // Значение узла
        T value;
        // Конструкторы узла
        Node() : p_next_node(nullptr) {}
        Node(T new_value) : p_next_node(nullptr), value(new_value) {}
    };
    // Вершина списка
    Node* m_head_node;

    // Получить последний узел
    Node* get_last_node()
    {
        if (m_head_node == nullptr || m_head_node->p_next_node == nullptr)
            return nullptr;
        auto lastNode = m_head_node;
        for (; lastNode->p_next_node->p_next_node != nullptr;
             lastNode = lastNode->p_next_node)
            ;
        return lastNode;
    }

public:
    // Класс итератора односвязного списка
    class List_iterator
    {
    public:
        // Конструктор класса
        List_iterator(Node* _node) : current_node(_node) {}
        // Операторы сравнения
        bool operator==(const List_iterator& iter)
        {
            if (this == &iter)
                return true;
            else
                return current_node == iter.current_node;
        }
        bool operator!=(const List_iterator& iter) { return !(this == iter); }
        // Оператор разыменования
        T operator*()
        {
            if (current_node != nullptr)
                return current_node->value;
            else
                return T();
        }
        // Оператор инкрементирования
        void operator++()
        {
            if (current_node != nullptr)
                current_node = current_node->p_next_node;
        }

    private:
        Node* current_node;
    };

    List_node() : m_head_node(nullptr){};  // Пустой конструктор
    // Конструктор списка по num_node количеству узлов в нём
    // (все узлы равны случайным числам с пределом random_range)
    List_node(const size_t num_node, const long random_range = -1)
        : m_head_node(nullptr)
    {
        for (size_t i = 0; i < num_node; ++i)
            if (random_range != -1)
                push(rand() % random_range);
            else
                push(T());
    }
    // Деструктор списка
    ~List_node() { clear(); }

    // Добавить new_value узел в начало списка
    void push(T new_value) override;
    // Добавить new_value узел в конец списка
    void push_back(T new_value) override;

    // Удалить первый узел
    T pop() override;
    // Удалить последний узел
    T pop_back() override;

    T top() override
    {
        if (auto node_ = get_last_node())
            return node_->value;
        else
            return T();
    }

    void clear() override
    {
        while (m_head_node != nullptr) pop();
    }
    // Вставить new_value узел в позицию index
    void insert(T new_value, const size_t index);

    // Получить значение узла в позиции index
    T get_node(const size_t index);

    // Получить количество узлов в списке
    size_t size() override;

    // Вывод всех элементов списка
    void print() override;
    // Ввод элементов списка
    void scan() override;

    // Возвращение итератора начала списка
    List_iterator begin() { return List_iterator(m_head_node); }
    // Возвращение итератора конца списка
    List_iterator end() { return List_iterator(nullptr); }

    // Создание массива (со ссылкой на длину arrayLen) из элементов списка
    T* list_to_array(size_t& array_len);
};

//*************************************
// Функции класса односвязного списка
//*************************************
// Добавить new_value узел в начало списка
template <typename T, auto MAX_LIST_SIZE, auto DELIM_CHR>
void List_node<T, MAX_LIST_SIZE, DELIM_CHR>::push(T new_value)
{
    // Выделение памяти под новый узел
    if (Node* new_node = new Node(new_value))
    {
        // Смена указателя на верхний узел
        new_node->p_next_node = m_head_node;
        // Перестановка указателя на новый верхний узел
        m_head_node = new_node;
    }
}

// Добавить new_value узел в конец списка
template <typename T, auto MAX_LIST_SIZE, auto DELIM_CHR>
void List_node<T, MAX_LIST_SIZE, DELIM_CHR>::push_back(T new_value)
{
    // Выделение памяти под первый узел и присвоение значений
    if (Node* new_node = new Node(new_value))
    {
        new_node->p_next_node = nullptr;
        // Получение указателя на последний узел
        auto lastNode = m_head_node;
        // Нахождение последнего элемента списка
        while (lastNode->p_next_node != nullptr)
            lastNode = lastNode->p_next_node;
        // Присвоение указателя
        lastNode->p_next_node = new_node;
    }
}

// Удалить первый узел
template <typename T, auto MAX_LIST_SIZE, auto DELIM_CHR>
T List_node<T, MAX_LIST_SIZE, DELIM_CHR>::pop()
{
    // Проверка на наличие узлов в списке
    if (m_head_node == nullptr) return T();
    // Создание указателя на вершину списка
    auto lastNode = m_head_node;
    T lastValue = lastNode->value;
    m_head_node = m_head_node->p_next_node;
    // Удаление узла
    free(lastNode);
    // Возвращение значения удалённого узла
    return lastValue;
}

// Удалить последний узел
template <typename T, auto MAX_LIST_SIZE, auto DELIM_CHR>
T List_node<T, MAX_LIST_SIZE, DELIM_CHR>::pop_back()
{
    // Проверка на наличие узлов в списке
    if (m_head_node == nullptr) return T();
    // Проверка на наличие одного узла в списке и его удаление
    if (m_head_node->p_next_node == nullptr)
    {
        delete m_head_node;
        m_head_node = nullptr;
        return T();
    }
    // Нахождение указателя на предпоследний узел
    // Создание указателя на предпоследний узел
    auto lastNode = get_last_node();

    // Значение последнего узла
    T lastValue = lastNode->p_next_node->value;
    // Удаление последнего узла
    delete lastNode->p_next_node;
    // Установка нулевого указателя
    lastNode->p_next_node = nullptr;
    // Возвращение значения удалённого узла
    return lastValue;
}

// Вставить new_value узел в позицию index
template <typename T, auto MAX_LIST_SIZE, auto DELIM_CHR>
void List_node<T, MAX_LIST_SIZE, DELIM_CHR>::insert(T new_value,
                                                    const size_t index)
{
    // Получение указателя на узел до индекса
    auto prev_node = m_head_node;
    size_t cnt = 0;
    while (cnt < index && prev_node != nullptr)
    {
        prev_node = prev_node->p_next_node;
        ++cnt;
    }

    // Создание нового узла
    if (auto new_node = new List_node(new_value))
    {
        // Вставка узла в нужную позицию
        new_node->p_next_node = prev_node->p_next_node;
        prev_node->p_next_node = new_node;
    }
}

// Получить значение узла в позиции index
template <typename T, auto MAX_LIST_SIZE, auto DELIM_CHR>
T List_node<T, MAX_LIST_SIZE, DELIM_CHR>::get_node(const size_t index)
{
    // Создание указателя на узел
    auto index_node = m_head_node;
    size_t cnt = 0;
    // Получение указателя на искомый узел
    while ((cnt++) < index && index_node != nullptr)
        index_node = index_node->p_next_node;
    // Возвращение значения узла
    return index_node->value;
}

// Вывод всех элементов списка
template <typename T, auto MAX_LIST_SIZE, auto DELIM_CHR>
void List_node<T, MAX_LIST_SIZE, DELIM_CHR>::print()
{
    // Получение размера списка
    size_t list_size = size();
    for (size_t index = 0; index < list_size; ++index)
        // Вывод элемента и символа разделителя
        std::cout << get_node(index) << DELIM_CHR;
    std::cout << std::endl;  // Вывод символа перевода каретки
}

// Ввод элементов списка
template <typename T, auto MAX_LIST_SIZE, auto DELIM_CHR>
void List_node<T, MAX_LIST_SIZE, DELIM_CHR>::scan()
{
    size_t size_list = 0;  // Размер списка
    // Ввод размера списка
    std::cout << "Enter the number of nodes in the list: ";
    do
    {
        std::cin >> size_list;
    } while (size_list < 0 || MAX_LIST_SIZE < size_list);

    T value = 0;
    std::cout << "Enter the value [0] list node: ";
    std::cin >> value;
    // Первый узел списка
    push_back(value);
    // Заполнение списка
    for (size_t i = 1; i < size_list; ++i)
    {
        std::cout << "Enter the value [" << i << "] list node: ";
        std::cin >> value;
        push_back(value);
    }
}

// Получить количество узлов в списке
template <typename T, auto MAX_LIST_SIZE, auto DELIM_CHR>
size_t List_node<T, MAX_LIST_SIZE, DELIM_CHR>::size()
{
    size_t size_list = 0;
    auto list_counter = m_head_node;
    // Подсчёт узлов до конца списка
    while (list_counter != nullptr)
    {
        ++size_list;
        list_counter = list_counter->p_next_node;
    }
    // Возвращение размера списка
    return size_list;
}

// Создание массива (со ссылкой на длину ArrayLen) из элементов списка с
// вершиной m_head_node
template <typename T, auto MAX_LIST_SIZE, auto DELIM_CHR>
T* List_node<T, MAX_LIST_SIZE, DELIM_CHR>::list_to_array(size_t& array_len)
{
    // Получение длины будущего массива (кол-ва узлов в списке)
    array_len = size();
    // Выделение памяти под массив
    auto arr = new T[array_len];
    // Заполнение массива
    for (size_t i = 0; i < array_len; ++i)
        // Получение значения из узла под индексом i
        arr[i] = GetList(m_head_node, i)->value;
    // Возвращение указателя на массив
    return arr;
}

#endif
