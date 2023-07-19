#pragma once
#include "core.hpp"

namespace ccat {

template<typename T, T first, T... seq>
struct prod_integer_of {
    static_assert(std::is_integral<T>::value, "type `T` must be integral");
    constexpr static T value = first * prod_integer_of<T, seq...>::value;
};

template<typename T, T t>
struct prod_integer_of<T, t> {
    static_assert(std::is_integral<T>::value, "type `T` must be integral");
    constexpr static T value = t;
};

template<typename IntSeq>
struct prod {
    static_assert(always_false<IntSeq>::value, "`IntSeq` must be `ccat::integer_sequence` or `std::integer_sequence`");
};

template<typename T, T... seq>
struct prod<integer_sequence<T, seq...>> {
    constexpr static T value = prod_integer_of<T, seq...>::value;
};

#if defined(__cplusplus) && __cplusplus >= CPP_STD14__ || defined(_MSVC_LANG ) && _MSVC_LANG >= CPP_STD14__

template<typename T, T... seq>
struct prod<std::integer_sequence<T, seq...>> {
    constexpr static T value = prod_integer_of<T, seq...>::value;
};

#endif


}
