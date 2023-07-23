#pragma once
#include "core.hpp"
#include "concat.hpp"

namespace ccat {
namespace detail {

template<typename T, T n, T first, T... seq>
struct remove_from_intseq_helper_ {
    using next = typename remove_from_intseq_helper_<T, n, seq...>::type;
    using type = typename std::conditional<
        n == first,
        next,
        concat<integer_sequence<T, first>, next>
    >::type;    
};
template<typename T, T n, T m>
struct remove_from_intseq_helper_<T, n, m> {
    using type = typename std::conditional<
        n == m,
        integer_sequence<T>,
        integer_sequence<T, m>
    >::type;
};

template<typename T, T n, typename IntSeq>
struct remove_from_intseq_ {
    static_assert(always_false<T>::value, "type `IntSeq` must be an `integer_sequence`");
};

template<typename T, T n, T... seq>
struct remove_from_intseq_<T, n, integer_sequence<T, seq...>> {
    static_assert(sizeof...(seq) > 0, "integer_sequence can't be empty");
    using type = typename remove_from_intseq_helper_<T, n, seq...>::type;
};

}

template<typename T, T n, typename IntSeq>
using remove_from = typename detail::remove_from_intseq_<T, n, IntSeq>::type;

}