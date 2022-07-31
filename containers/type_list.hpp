#ifndef __TYPE_LIST__
#define __TYPE_LIST__

#include <iostream>

namespace types
{

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
template <typename... Args>
struct type_list;

template <typename... Args>
struct type_list
{
    using head = empty_type;
    using tail = empty_type;
};
// Пустой список
using empty_list = type_list<>;

// Размер списка
template <class>
struct length_t;

template <>
struct length_t<empty_list>
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

// Проверка на пустой список
template <class tlist>
struct empty_t
{
    static constexpr auto value = same_t<tlist, empty_list>::value ? 1 : 0;
};

// Проверка на наличие элемента в списке
template <class tlist, typename T>
struct in_t
{
    static constexpr auto value = in_t<typename tlist::tail, T>::value;
};

template <typename T>
struct in_t<empty_list, T>
{
    static constexpr auto value = 0;
};

template <typename T, typename... Args>
struct in_t<type_list<T, Args...>, T>
{
    static constexpr auto value = 1;
};

template <class, typename, size_t>
struct _index_t;

template <typename T, size_t N>
struct _index_t<empty_list, T, N>
{
    static constexpr auto value = 0;
};

template <class tlist, typename T, size_t N>
struct _index_t
{
    static constexpr auto value =
        same_t<T, typename tlist::head>::value
            ? N
            : N + 1 + _index_t<typename tlist::tail, T, N>::value;
};

// Индекс элемента
template <class tlist, typename T>
struct index_t
{
    static constexpr long value =
        in_t<tlist, T>::value ? _index_t<tlist, T, 0>::value : -1;
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

// Удаление элементов из списка
template <typename tlist, typename T>
struct remove_t
{
private:
    using del_ = typename remove_t<typename tlist::tail, T>::value;
    using head_ = typename tlist::head;

public:
    using value =
        typename if_t<same_t<head_, T>::value, del_,
                      typename add_t<type_list<head_>, del_>::value>::value;
};

template <typename T>
struct remove_t<empty_list, T>
{
    using value = empty_type;
};

template <typename Head, typename T>
struct remove_t<type_list<Head>, T>
{
    using value = typename if_t<same_t<Head, T>::value, empty_list,
                                type_list<Head>>::value;
};

// Вывод списка
std::ostream& operator<<(std::ostream& out, empty_list)
{
    out << "<>";
    return out;
}

template <class T>
void print_type(std::ostream& out, T)
{
    out << typeid(T).name();
}

template <typename... Args>
void print_type(std::ostream& out, type_list<Args...> t)
{
    out << t;
}

template <typename T>
void print_list(std::ostream&, T);

template <typename T, typename... Args>
void print_list(std::ostream& out, type_list<T, Args...>)
{
    using this_list = type_list<Args...>;
    print_type(out, T());
    if (!empty_t<this_list>::value)
    {
        out << ' ';
        print_list(out, this_list());
    }
}

template <typename... Args>
std::ostream& operator<<(std::ostream& out, type_list<Args...> t)
{
    out << '<';
    print_list(out, t);
    out << '>';
    return out;
}

template <typename Head, typename... Tail>
class type_list<Head, Tail...>
{
    using tlist = type_list<Head, Tail...>;

public:
    using head = Head;
    using tail = type_list<Tail...>;
    static constexpr size_t length = length_t<tlist>::value;
    template <size_t N>
    using get = typename type_at_t<tlist, N>::value;
    template <typename T>
    static constexpr auto index = index_t<tlist, T>::value;

    template <typename T>
    using push = typename push_t<tlist, T>::value;

    template <typename T>
    using remove = typename remove_t<tlist, T>::value;

    template <typename... Args2>
    using append = typename append_t<tlist, Args2...>::value;

    template <typename... Args2>
    using add = typename add_t<tlist, Args2...>::value;

    friend std::ostream& operator<<(std::ostream& out, tlist t)
    {
        out << '<';
        print_list(out, t);
        out << '>';
        return out;
    }
};
};  // namespace types

/* int main(int argc, char* argv[]) */
/* { */
/*     using t1 = type_list<int, char, bool, type_list<float, double>, long>; */
/*     std::cout << t1() << std::endl; */
/* } */

#endif /* ifndef __TYPE_LIST__ */
