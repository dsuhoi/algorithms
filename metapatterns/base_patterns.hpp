#ifndef __BASE_PATTERNS__
#define __BASE_PATTERNS__

namespace types
{
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

// Представление констант в виде типов
template <int i>
struct int2type
{
    static constexpr auto value = i;
};

}  // namespace types

#endif /* ifndef __BASE_PATTERNS__ */
