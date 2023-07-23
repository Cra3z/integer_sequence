#pragma once
#include "remove_from.hpp"

namespace ccat {
namespace detail {
    
template<typename T, T first, T... seq>
struct unique_helper_;

template<typename T, T... seq>
constexpr auto unique_helper_fn_(integer_sequence<T, seq...>) noexcept -> typename unique_helper_<T, seq...>::type;
template<typename T>
constexpr auto unique_helper_fn_(integer_sequence<T>) noexcept -> integer_sequence<T>;

template<typename T, T first, T... seq>
struct unique_helper_ {
    using type = concat<integer_sequence<T, first>, decltype(
        unique_helper_fn_(std::declval<typename remove_from_intseq_helper_<T, first, seq...>::type>())
    )>;
};
template<typename T, T first, T second>
struct unique_helper_<T, first, second> {
    using type = typename std::conditional<
        first == second,
        integer_sequence<T, first>,
        integer_sequence<T, first, second>
    >::type;
};

template<typename T, T n>
struct unique_helper_<T, n> {
    using type = integer_sequence<T, n>;
};


template<typename IntSeq>
struct unique_intseq_helper_ {
    static_assert(always_false<IntSeq>::value, "`IntSeq` must be an `integer_sequence`");
};
template<typename T, T... seq>
struct unique_intseq_helper_<integer_sequence<T, seq...>> {
    using type = unique_helper_<T, seq...>;
};

}

template<typename T, T... seq>
using make_unique_integer_sequence = typename detail::unique_helper_<T, seq...>::type;

template<typename IntSeq>
using unique = typename detail::unique_intseq_helper_<IntSeq>::type;

}