#ifndef __TYPE_LIST__
#define __TYPE_LIST__

#include <iostream>

// Флаг ошибок
class null_type;
// Флаг конца списка
class empty_type;

// Сравнение типов
template <typename U, typename T>
struct same_t
{
    enum
    {
        value = false
    };
};

template <typename U>
struct same_t<U, U>
{
    enum
    {
        value = true
    };
};

// Тернарный оператор типов
template <bool, typename U, typename T>
struct if_t
{
    using value = U;
};

template <typename U, typename T>
struct if_t<false, U, T>
{
    using value = T;
};

// Список типов
template <typename Head, typename... Tail>
struct type_list
{
    using head = Head;
    using tail = type_list<Tail...>;
};

template <typename T>
struct type_list<T>
{
    using head = T;
    using tail = empty_type;
};

// Определение размера списка
template <class>
struct length_t;

template <>
struct length_t<empty_type>
{
    enum
    {
        value = 0
    };
};

template <class tlist>
struct length_t
{
    enum
    {
        value = 1 + length_t<typename tlist::tail>::value
    };
};

// Получение элемента по индексу
template <class, size_t>
struct index_t;

template <>
struct index_t<empty_type, 0>
{
    using value = null_type;
};

template <size_t N>
struct index_t<empty_type, N>
{
    using value = null_type;
};

template <class tlist>
struct index_t<tlist, 0>
{
    using value = typename tlist::head;
};

template <class tlist, size_t N>
struct index_t
{
    using value = typename index_t<typename tlist::tail, N - 1>::value;
};

// Добавление элемента в начало списка
template <class tlist, typename T>
struct push_t
{
    using value = type_list<T, tlist>;
};

#endif /* ifndef __TYPE_LIST__ */
