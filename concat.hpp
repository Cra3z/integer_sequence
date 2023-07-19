#pragma once
#include "core.hpp"

namespace ccat {
namespace detail {
template<typename T, T first1, T... seq1, T first2, T... seq2>
constexpr auto int_seq_cat_helper_fn_(integer_sequence<T, first1, seq1...>, integer_sequence<T, first2, seq2...>) noexcept
->integer_sequence<T, first1, seq1..., first2, seq2...>;

template<typename int_seq1, typename int_seq2>
struct concat_ {
    static_assert(
        (is_ccat_integer_sequence<int_seq1>::value
#if defined(__cplusplus) && __cplusplus >= CPP_STD14__ || defined(_MSVC_LANG ) && _MSVC_LANG >= CPP_STD14__ 
        || is_std_integer_sequence<int_seq1>::value) && (is_std_integer_sequence<int_seq2>::value
        || is_ccat_integer_sequence<int_seq2>::value)
#else      
        && is_ccat_integer_sequence<int_seq2>::value)
#endif
        ,"`IntSeq` must be `ccat::integer_sequence` or `std::integer_sequence`"
    );
    using type = decltype(int_seq_cat_helper_fn_(std::declval<int_seq1>(),
                                               std::declval<int_seq2>()));
};
}

template<typename int_seq1, typename int_seq2>
using concat = typename detail::concat_<int_seq1, int_seq2>::type;

}