#ifndef __LIST_LIB_HPP__
#define __LIST_LIB_HPP__

#include <cstddef>
#include <iostream>

#include "data_interface.hpp"

// Класс односвязного списка
template <typename T, const size_t MAX_LIST_SIZE = 1000>
class list_t : public data_interface<T>
{
    struct node_t
    {
        node_t* p_next_node;
        T value;
        node_t() : p_next_node(nullptr) {}
        node_t(T new_value) : p_next_node(nullptr), value(new_value) {}
    };
    // Вершина списка
    node_t* m_head_node;

    node_t* get_last_node()
    {
        if (m_head_node == nullptr || m_head_node->p_next_node == nullptr)
            return nullptr;
        auto last_node = m_head_node;
        for (; last_node->p_next_node->p_next_node != nullptr;
             last_node = last_node->p_next_node)
            ;
        return last_node;
    }

public:
    // Класс итератора односвязного списка
    class list_iterator
    {
    public:
        list_iterator(node_t* _node) : current_node(_node) {}
        bool operator==(const list_iterator& iter)
        {
            if (this == &iter)
                return true;
            else
                return current_node == iter.current_node;
        }
        bool operator!=(const list_iterator& iter) { return !(this == iter); }
        T operator*()
        {
            if (current_node != nullptr)
                return current_node->value;
            else
                return T();
        }
        void operator++()
        {
            if (current_node != nullptr)
                current_node = current_node->p_next_node;
        }

    private:
        node_t* current_node;
    };

    list_t() : m_head_node(nullptr){};
    list_t(const size_t num_node, const long random_range = -1)
        : m_head_node(nullptr)
    {
        for (size_t i = 0; i < num_node; ++i)
            if (random_range != -1)
                push(rand() % random_range);
            else
                push(T());
    }
    ~list_t() { clear(); }

    void push(T new_value) override
    {
        if (node_t* new_node = new node_t(new_value))
        {
            new_node->p_next_node = m_head_node;
            m_head_node = new_node;
        }
    }
    void push_back(T new_value) override
    {
        if (node_t* new_node = new node_t(new_value))
        {
            new_node->p_next_node = nullptr;
            auto last_node = m_head_node;
            while (last_node->p_next_node != nullptr)
                last_node = last_node->p_next_node;
            last_node->p_next_node = new_node;
        }
    }

    T pop() override
    {
        if (m_head_node == nullptr) return T();
        auto last_node = m_head_node;
        T last_value = last_node->value;
        m_head_node = m_head_node->p_next_node;
        delete last_node;
        return last_value;
    }
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
    void insert(T new_value, const size_t index);

    T get(const size_t index);

    size_t size() override
    {
        size_t size_list = 0;
        auto list_counter = m_head_node;
        while (list_counter != nullptr)
        {
            ++size_list;
            list_counter = list_counter->p_next_node;
        }
        return size_list;
    }

    friend std::ostream& operator<<(std::ostream& out, list_t& list_)
    {
        size_t list_size = list_.size();
        for (size_t index = 0; index < list_size; ++index)
            out << list_.get(index) << ' ';
        return out;
    }

    list_iterator begin() { return list_iterator(m_head_node); }
    list_iterator end() { return list_iterator(nullptr); }

    // Создание массива (со ссылкой на длину array_len) из элементов списка
    T* list2array(size_t& array_len);
};

template <typename T, const size_t MAX_LIST_SIZE>
T list_t<T, MAX_LIST_SIZE>::pop_back()
{
    if (m_head_node == nullptr) return T();
    if (m_head_node->p_next_node == nullptr)
    {
        delete m_head_node;
        m_head_node = nullptr;
        return T();
    }
    auto last_node = get_last_node();

    T last_value = last_node->p_next_node->value;
    delete last_node->p_next_node;
    last_node->p_next_node = nullptr;
    return last_value;
}

template <typename T, const size_t MAX_LIST_SIZE>
void list_t<T, MAX_LIST_SIZE>::insert(T new_value, const size_t index)
{
    if (index <= 0)
    {
        push(new_value);
    }
    else if (MAX_LIST_SIZE <= index)
    {
        push_back(new_value);
    }
    else
    {
        auto prev_node = m_head_node;
        size_t cnt = 1;
        while (cnt < index && index < MAX_LIST_SIZE && prev_node != nullptr)
        {
            prev_node = prev_node->p_next_node;
            ++cnt;
        }

        if (auto new_node = new node_t(new_value))
        {
            new_node->p_next_node = prev_node->p_next_node;
            prev_node->p_next_node = new_node;
        }
    }
}

template <typename T, const size_t MAX_LIST_SIZE>
T list_t<T, MAX_LIST_SIZE>::get(const size_t index)
{
    auto index_node = m_head_node;
    size_t cnt = 0;
    while ((cnt++) < index && index_node != nullptr)
        index_node = index_node->p_next_node;
    return index_node->value;
}

template <typename T, const size_t MAX_LIST_SIZE>
T* list_t<T, MAX_LIST_SIZE>::list2array(size_t& array_len)
{
    array_len = size();
    auto arr = new T[array_len];
    for (size_t i = 0; i < array_len; ++i)
        arr[i] = GetList(m_head_node, i)->value;
    return arr;
}

#endif
