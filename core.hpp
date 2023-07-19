#pragma once
#include <cstddef>
#include <type_traits>
#include <utility>
#include "config.hpp"
#include "type_sequence.hpp"
namespace ccat {

template<typename T, T... seq>
struct integer_sequence {
    static_assert(std::is_integral<T>::value, "type `T` must be integral");
    using value_type = T;
    constexpr static auto size() noexcept ->size_t {
        return sizeof...(seq);
    }
#if defined(__cplusplus) && __cplusplus >= CPP_STD14__ || defined(_MSVC_LANG ) && _MSVC_LANG >= CPP_STD14__
    using to_std = std::integer_sequence<T, seq...>;
#endif
};

template<size_t... seq>
using index_sequence = integer_sequence<size_t, seq...>;

template<typename T, T N>
class make_int_seq_helper_ {
    static_assert(std::is_integral<T>::value, "type `T` must be integral");
    static_assert(N > 0, "`N` must be greater than 0");
private:
    template<T N_, T... rests>
    struct impl : impl<N_-1, N_, rests...> {};

    template<T... rests>
    struct impl<0, rests...> {
        using type = integer_sequence<T, 0, rests...>;
    };
public:
    using result = typename impl<N-1>::type;
};

template<typename T, T N> // => integer_sequence<0, 1, ..., N-1>
using make_integer_sequence = typename make_int_seq_helper_<T, N>::result;

template<size_t N>
using make_index_sequence = make_integer_sequence<size_t, N>;

template<typename T, T N>
struct from {
    static_assert(std::is_integral<T>::value, "type `T` must be integral");
private:
    template<T N_, T... rests>
    struct impl : impl<N_-1, N_, rests...> {};

    template<T... rests>
    struct impl<N, rests...> {
        using type = integer_sequence<T, N, rests...>;
    };
public:
    template<T M>
    struct to {
        static_assert(M >= N, "`M` must be greater than or equal to `N`");
        using type = typename impl<M>::type;
    };
};

template<typename T, T N, T M>
using from_to_t = typename from<T, N>::template to<M>::type;

template<typename IntSeq>    
struct is_ccat_integer_sequence : std::false_type {};
template<typename T, T... seq>
struct is_ccat_integer_sequence<integer_sequence<T, seq...>> : std::true_type {};

#if defined(__cplusplus) && __cplusplus >= CPP_STD14__ || defined(_MSVC_LANG ) && _MSVC_LANG >= CPP_STD14__
template<typename IntSeq>    
struct is_std_integer_sequence : std::false_type {};
template<typename T, T... seq>
struct is_std_integer_sequence<std::integer_sequence<T, seq...>> : std::true_type {};
////////////////////////////////////////////
template<typename IntSeq>
constexpr bool is_ccat_integer_sequence_v = is_ccat_integer_sequence<IntSeq>::value;
template<typename IntSeq>
constexpr bool is_std_integer_sequence_v = is_std_integer_sequence<IntSeq>::value;

template<typename IntSeq>
struct from_std_integer_sequence {
    static_assert(is_std_integer_sequence<IntSeq>::value, "`IntSeq` must be a `std::integer_sequence<T, ...>`");
};
template<typename T, T... seq>
struct from_std_integer_sequence<std::integer_sequence<T, seq...>> {
    using type = integer_sequence<T, seq...>;
};
template<typename IntSeq>
struct to_std_integer_sequence {
    static_assert(is_ccat_integer_sequence<IntSeq>::value, "`IntSeq` must be a `ccat::integer_sequence<T, ...>`");
};
template<typename T, T... seq>
struct to_std_integer_sequence<integer_sequence<T, seq...>> {
    using type = std::integer_sequence<T, seq...>;
};

template<typename IntSeq>
using from_std_integer_sequence_t = typename from_std_integer_sequence<IntSeq>::type;
template<typename IntSeq>
using to_std_integer_sequence_t = typename to_std_integer_sequence<IntSeq>::type;

#endif

}    
