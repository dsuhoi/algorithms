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
    static constexpr auto value = false;
};

template <typename U>
struct same_t<U, U>
{
    static constexpr auto value = true;
};

// Тернарный оператор
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

// Размер списка
template <class>
struct length_t;

template <>
struct length_t<empty_type>
{
    static constexpr auto value = 0;
};

template <typename tlist>
struct length_t
{
    static constexpr auto value = 1 + length_t<typename tlist::tail>::value;
};

// Получение элемента по индексу
template <class, size_t>
struct type_at_t;

template <class tlist>
struct type_at_t<tlist, 0>
{
    using value = typename tlist::head;
};

template <class tlist, size_t N>
struct type_at_t
{
    static_assert(N < length_t<tlist>::value, "Error: N index in type list!");
    using value = typename type_at_t<typename tlist::tail, N - 1>::value;
};

// Добавление элемента в конец списка
template <typename, typename>
struct append_t;

template <typename T, typename... Args>
struct append_t<type_list<Args...>, T>
{
    using value = type_list<Args..., T>;
};

// Добавление элемента в начало списка
template <typename, typename>
struct push_t;

template <typename T, typename... Args>
struct push_t<type_list<Args...>, T>
{
    using value = type_list<T, Args...>;
};

// Склейка списков
template <typename, typename>
struct add_t;

template <typename T, typename... Args>
struct add_t<type_list<Args...>, T>
{
    using value = type_list<Args..., T>;
};

template <typename... Args1, typename... Args2>
struct add_t<type_list<Args1...>, type_list<Args2...>>
{
    using value = type_list<Args1..., Args2...>;
};

#endif /* ifndef __TYPE_LIST__ */
