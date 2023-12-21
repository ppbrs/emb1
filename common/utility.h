#pragma once

#include <variant>

/*
Get the index of a type.
Inspired by https://stackoverflow.com/questions/52303316/get-index-by-type-in-stdvariant
*/
template<typename T, typename V>
struct get_variant_type_index;

template<typename>
struct tag {};

template<typename T, typename... Ts>
struct get_variant_type_index<T, std::variant<Ts...>>
		: std::integral_constant<std::size_t, std::variant<tag<Ts>...>(tag<T>()).index()> {
};
