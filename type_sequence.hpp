#pragma once
#include <type_traits>
namespace ccat {

template<typename... Args>
struct type_sequence {
    constexpr static size_t size = sizeof...(Args);
};
template<typename...>
struct always_false {
    constexpr static bool value = false;
};

namespace detail {

template<typename... Tys1, typename... Tys2>
constexpr auto concat_type_sequence_helper_fn_(type_sequence<Tys1...>, type_sequence<Tys2...>) noexcept -> type_sequence<Tys1..., Tys2...>;
template<typename TySeq1, typename TySeq2>
using concat_type_sequences = decltype(concat_type_sequence_helper_fn_(std::declval<TySeq1>(), std::declval<TySeq2>()));

template<typename T, typename U, typename... Types>
struct remove_from_types_impl_ {
    using next = typename remove_from_types_impl_<T, Types...>::type;
    using type = typename std::conditional<
        std::is_same<T, U>::value,
        next,
        concat_type_sequences<type_sequence<U>, next>
    >::type;
};
template<typename T, typename U>
struct remove_from_types_impl_<T, U> {
    using type = typename std::conditional<
        std::is_same<T, U>::value,
        type_sequence<>,
        type_sequence<U>
    >::type;
};

template<typename T, typename TySeq>
struct remove_from_type_sequence_ {
    static_assert(always_false<T>::value, "type `TySeq` must be a `ccat::type_sequence` and its static member `size` must be greater than 0");
};
template<typename T, typename U, typename... Types>
struct remove_from_type_sequence_<T, type_sequence<U, Types...>> {
    using type = typename remove_from_types_impl_<T, U, Types...>::type;
};

template<typename T, typename... Types>
using remove_from_types = typename remove_from_types_impl_<T, Types...>::type;
template<typename T, typename TySeq>
using remove_from_type_sequence_t = typename remove_from_types_impl_<T, TySeq>::type;

template<typename T, typename... Types>
struct tyseq_unique;

template<typename... Types>
constexpr auto unique_type_sequence_helper_fn_(type_sequence<Types...>) noexcept -> typename tyseq_unique<Types...>::type;
constexpr auto unique_type_sequence_helper_fn_(type_sequence<>) noexcept ->type_sequence<>;

template<typename T, typename... Types>
struct tyseq_unique {
    using type = concat_type_sequences<type_sequence<T>, decltype(unique_type_sequence_helper_fn_(std::declval<remove_from_types<T, Types...>>()))>;
};
template<typename T, typename U>
struct tyseq_unique<T, U> {
    using type = typename std::conditional<std::is_same<T, U>::value, type_sequence<T>, type_sequence<T, U>>::type;
};
template<typename T>
struct tyseq_unique<T> {
    using type = type_sequence<T>;
};

}

template<typename T, typename... Types>
using make_unique_type_sequence = typename detail::tyseq_unique<T, Types...>::type; 

template<typename T, typename TySeq>
using remove_a_type_from_type_sequence = detail::remove_from_type_sequence_t<T, TySeq>;

template<typename TySeq1, typename TySeq2>
using type_sequence_concat = detail::concat_type_sequences<TySeq1, TySeq2>;

}
