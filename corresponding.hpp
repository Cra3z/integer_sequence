#pragma once
#include "concat.hpp"

namespace ccat {

template<typename T, T first1, T first2>
constexpr auto int_seq_add_helper_fn_(integer_sequence<T, first1>, integer_sequence<T, first2>) noexcept ->integer_sequence<T, first1 + first2>;

template<typename T, T first1, T first2, T... seq1, T... seq2>
constexpr auto int_seq_add_helper_fn_(integer_sequence<T, first1, seq1...>, integer_sequence<T, first2, seq2...>) noexcept
->concat<
    integer_sequence<T, first1 + first2>,
    decltype(int_seq_add_helper_fn_(
        std::declval<integer_sequence<T, seq1...>>(), std::declval<integer_sequence<T, seq2...>>()
    ))
>;

template<typename int_seq1, typename int_seq2>
struct integer_sequence_add {
    static_assert(int_seq1::size() == int_seq2::size(), "The size of two integer sequences must be consistent");
    using type = decltype(int_seq_add_helper_fn_(std::declval<int_seq1>(), std::declval<int_seq2>()));
};

///////////////////////////////////////////
//////////////////////////////////////////
template<typename T, T first1, T first2>
constexpr auto int_seq_subtract_helper_fn_(integer_sequence<T, first1>, integer_sequence<T, first2>) noexcept ->integer_sequence<T, first1 - first2>;

template<typename T, T first1, T first2, T... seq1, T... seq2>
constexpr auto int_seq_subtract_helper_fn_(integer_sequence<T, first1, seq1...>, integer_sequence<T, first2, seq2...>) noexcept
->concat<
    integer_sequence<T, first1 - first2>,
    decltype(int_seq_subtract_helper_fn_(
        std::declval<integer_sequence<T, seq1...>>(), std::declval<integer_sequence<T, seq2...>>()
    ))
>;

template<typename int_seq1, typename int_seq2>
struct integer_sequence_subtract {
    static_assert(int_seq1::size() == int_seq2::size(), "The size of two integer sequences must be consistent");
    using type = decltype(int_seq_subtract_helper_fn_(std::declval<int_seq1>(), std::declval<int_seq2>()));
};

//////////////////////////////////////////
template<typename T, T first1, T first2>
constexpr auto int_seq_multiply_helper_fn_(integer_sequence<T, first1>, integer_sequence<T, first2>) noexcept ->integer_sequence<T, first1 * first2>;

template<typename T, T first1, T first2, T... seq1, T... seq2>
constexpr auto int_seq_multiply_helper_fn_(integer_sequence<T, first1, seq1...>, integer_sequence<T, first2, seq2...>) noexcept
->concat<
    integer_sequence<T, first1 * first2>,
    decltype(int_seq_multiply_helper_fn_(
        std::declval<integer_sequence<T, seq1...>>(), std::declval<integer_sequence<T, seq2...>>()
    ))
>;

template<typename int_seq1, typename int_seq2>
struct integer_sequence_multiply {
    static_assert(int_seq1::size == int_seq2::size, "The size of two integer sequences must be consistent");
    using type = decltype(int_seq_multiply_helper_fn_(std::declval<int_seq1>(), std::declval<int_seq2>()));
};

template<typename int_seq1, typename int_seq2>
using add = typename integer_sequence_add<int_seq1, int_seq2>::type;

template<typename int_seq1, typename int_seq2>
using subtract = typename integer_sequence_subtract<int_seq1, int_seq2>::type;

template<typename int_seq1, typename int_seq2>
using multiply = typename integer_sequence_multiply<int_seq1, int_seq2>::type;


}