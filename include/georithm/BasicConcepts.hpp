//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_BASIC_CONCEPTS_HPP
#define GEORITHM_BASIC_CONCEPTS_HPP

#pragma once

#include <concepts>
#include <iterator>
#include <type_traits>

namespace georithm
{
	template <class T, class T2 = T>
	concept AddAssignable = requires(T lhs, T2 rhs)
	{
		{ lhs += rhs };
	};

	template <class T, class T2 = T>
	concept SubtractAssignable = requires(T lhs, T2 rhs)
	{
		{ lhs -= rhs };
	};

	template <class T, class T2 = T>
	concept MultiplyAssignable = requires(T lhs, T2 rhs)
	{
		{ lhs *= rhs };
	};

	template <class T, class T2 = T>
	concept DivideAssignable = requires(T lhs, T2 rhs)
	{
		{ lhs /= rhs };
	};

	template <class T, class T2 = T>
	concept ModuloAssignable = requires(T lhs, T2 rhs)
	{
		{ lhs %= rhs };
	};

	template <class T, class T2 = T>
	concept Addable = AddAssignable<T, T2> && requires(T lhs, T2 rhs)
	{
		{ lhs + rhs }->std::convertible_to<T>;
	};

	template <class T, class T2 = T>
	concept Subtractable = SubtractAssignable<T, T2> && requires(T lhs, T2 rhs)
	{
		{ lhs - rhs } -> std::convertible_to<T>;
	};

	template <class T, class T2 = T>
	concept Multiplicable = MultiplyAssignable<T, T2> && requires(T lhs, T2 rhs)
	{
		{ lhs * rhs } -> std::convertible_to<T>;
	};

	template <class T, class T2 = T>
	concept Divisable = DivideAssignable<T, T2> && requires(T lhs, T2 rhs)
	{
		{ lhs / rhs } -> std::convertible_to<T>;
	};

	template <class T, class T2 = T>
	concept Moduloable = ModuloAssignable<T, T2> && requires(T lhs, T2 rhs)
	{
		{ lhs % rhs }->std::convertible_to<T>;
	};

	template <class T>
	concept ForwardIteratable = requires(std::remove_cvref_t<T>& object)
	{
		{ std::begin(object) }->std::forward_iterator;
		{ std::end(object) }->std::sentinel_for<decltype(std::begin(object))>;
	};

	template <class T>
	concept ConstForwardIteratable = requires(const std::remove_cvref_t<T>& object)
	{
		{ std::begin(object) } -> std::forward_iterator;
		{ std::cbegin(object) } -> std::forward_iterator;
		{ std::end(object) } -> std::sentinel_for<decltype(std::cbegin(object))>;
		{ std::cend(object) } -> std::sentinel_for<decltype(std::cbegin(object))>;
	};

	template <class T>
	concept BiDirectionalIteratable = ForwardIteratable<T> && requires(std::remove_cvref_t<T>& object)
	{
		{ std::rbegin(object) } -> std::bidirectional_iterator;
		{ std::rend(object) } -> std::sentinel_for<decltype(std::rbegin(object))>;
	};

	template <class T>
	concept ConstBiDirectionalIteratable = ConstForwardIteratable<T> && requires(const std::remove_cvref_t<T>& object)
	{
		{ std::rbegin(object) } -> std::bidirectional_iterator;
		{ std::crbegin(object) } -> std::bidirectional_iterator;
		{ std::rend(object) } -> std::sentinel_for<decltype(std::crbegin(object))>;
		{ std::crend(object) } -> std::sentinel_for<decltype(std::crbegin(object))>;
	};

	template <class TFn, class R, class... TArgs>
	concept invocable_r = std::is_invocable_r_v<R, TFn, TArgs...>;

	template <class TFrom, class TTo>
	concept implicit_convertible_to = std::is_convertible_v<TFrom, TTo>;
}

#endif
