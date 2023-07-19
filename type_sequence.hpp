#pragma once
namespace ccat {
template<typename... Args>
struct type_sequence {
    constexpr static size_t size = sizeof...(Args);
};
template<typename...>
struct always_false {constexpr static bool value = false;};
}