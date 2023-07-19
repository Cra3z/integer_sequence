#pragma once
#include "core.hpp"

namespace ccat {
namespace detail {
template<size_t N, typename T, T M, T... Ms>
struct repeat_helper_ : repeat_helper_<N-1, T, M, M, Ms...> {};

template<typename T, T M, T... Ms>
struct repeat_helper_<1, T, M, Ms...> {
    using result = integer_sequence<T, M, Ms...>;
};

template<size_t N, typename T, T M>
struct repeat_ {
    static_assert(N > 0, "`N` must be greater than 0");
    using type = typename repeat_helper_<N, T, M>::result;
};
}

template <size_t N, typename T, T M>
using repeat = typename detail::repeat_<N, T, M>::type;

}