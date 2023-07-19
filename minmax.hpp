#pragma once
#include "core.hpp"

namespace ccat {

template<typename T, T first, T second, T... rests>
struct max_integer_of : max_integer_of<T, (first > second ? first : second), rests...> {
    static_assert(std::is_integral<T>::value, "type `T` must be integral");
};

template<typename T, T a, T b>
struct max_integer_of<T, a, b> {
    static_assert(std::is_integral<T>::value, "type `T` must be integral");
    constexpr static T value = a > b ? a : b;
};

template<size_t... seq>
using max_size_of = max_integer_of<size_t, seq...>;

template<typename firstTy, typename secondTy, typename... Types>
struct max_type_of : max_type_of<typename max_type_of<firstTy, secondTy>::type, Types...> {};

template<typename firstTy, typename secondTy>
struct max_type_of<firstTy, secondTy> {
    using type = typename std::conditional<max_size_of<sizeof(firstTy), sizeof(secondTy)>::value == sizeof(firstTy), firstTy, secondTy>::type;
};

template<typename firstTy, typename secondTy, typename... Types>
using max_type_of_t = typename max_type_of<firstTy, secondTy, Types...>::type;

template<typename IntSeq>
struct max_of {
    static_assert(always_false<IntSeq>::value, "`IntSeq` must be `ccat::integer_sequence` or `std::integer_sequence`");
};
template<typename T, T... seq>
struct max_of<integer_sequence<T, seq...>> {
    constexpr static T value = max_integer_of<T, seq...>::value;
};

#if defined(__cplusplus) && __cplusplus >= CPP_STD14__ || defined(_MSVC_LANG ) && _MSVC_LANG >= CPP_STD14__

template<typename T, T... seq>
constexpr T max_integer_of_v = max_integer_of<T, seq...>::value;

template<size_t... seq>
constexpr size_t max_size_of_v = max_size_of<seq...>::value;

template<typename T, T... seq>
struct max_of<std::integer_sequence<T, seq...>> {
    constexpr static T value = max_integer_of<T, seq...>::value;
};

#endif

/////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////

template<typename T, T first, T second, T... rests>
struct min_integer_of : min_integer_of<T, (first < second ? first : second), rests...> {
    static_assert(std::is_integral<T>::value, "type `T` must be integral");
};

template<typename T, T a, T b>
struct min_integer_of<T, a, b> {
    static_assert(std::is_integral<T>::value, "type `T` must be integral");
    constexpr static T value = a < b ? a : b;
};

template<size_t... seq>
using min_size_of = min_integer_of<size_t, seq...>;

template<typename firstTy, typename secondTy, typename... Types>
struct min_type_of : min_type_of<typename min_type_of<firstTy, secondTy>::type, Types...> {};

template<typename firstTy, typename secondTy>
struct min_type_of<firstTy, secondTy> {
    using type = typename std::conditional<min_size_of<sizeof(firstTy), sizeof(secondTy)>::value == sizeof(firstTy), firstTy, secondTy>::type;
};

template<typename firstTy, typename secondTy, typename... Types>
using min_type_of_t = typename min_type_of<firstTy, secondTy, Types...>::type;


template<typename IntSeq>
struct min_of {
    static_assert(always_false<IntSeq>::value, "`IntSeq` must be `ccat::integer_sequence` or `std::integer_sequence`");
};
template<typename T, T... seq>
struct min_of<integer_sequence<T, seq...>> {
    constexpr static T value = min_integer_of<T, seq...>::value;
};

#if defined(__cplusplus) && __cplusplus >= CPP_STD14__ || defined(_MSVC_LANG ) && _MSVC_LANG >= CPP_STD14__

template<typename T, T... seq>
constexpr T min_integer_of_v = min_integer_of<T, seq...>::value;

template<size_t... seq>
constexpr size_t min_size_of_v = min_size_of<seq...>::value;

template<typename T, T... seq>
struct min_of<std::integer_sequence<T, seq...>> {
    constexpr static T value = min_integer_of<T, seq...>::value;
};

#endif


}
