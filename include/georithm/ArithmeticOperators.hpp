
//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_ARITHMETIC_OPERATORS_HPP
#define GEORITHM_ARITHMETIC_OPERATORS_HPP

#pragma once

#include <compare>
#include "Concepts.hpp"

namespace georithm
{
	template <class T>
	struct Plus
	{
		template <class U>
		requires AddAssignable<T, U>
		friend constexpr T operator +(T lhs, const U& rhs)
		{
			return lhs += rhs;
		}

		constexpr auto operator <=>(const Plus&) const = default;
	};

	template <class T>
	struct Minus
	{
		template <class U>
		requires SubtractAssignable<T, U>
		friend constexpr T operator -(T lhs, const U& rhs)
		{
			return lhs -= rhs;
		}

		constexpr auto operator <=>(const Minus&) const = default;
	};

	template <class T>
	struct Multiply
	{
		template <class U>
		requires MultiplyAssignable<T, U>
		friend constexpr T operator *(T lhs, const U& rhs)
		{
			return lhs *= rhs;
		}

		constexpr auto operator <=>(const Multiply&) const = default;
	};

	template <class T>
	struct Divide
	{
		template <class U>
		requires DivideAssignable<T, U>
		friend constexpr T operator /(T lhs, const U& rhs)
		{
			return lhs /= rhs;
		}

		constexpr auto operator <=>(const Divide&) const = default;
	};

	template <class T>
	struct Modulo
	{
		template <class U>
		requires ModuloAssignable<T, U>
		friend constexpr T operator %(T lhs, const U& rhs)
		{
			return lhs %= rhs;
		}

		constexpr auto operator <=>(const Modulo&) const = default;
	};

	template <class T>
	struct Arithmetic :
		Plus<T>,
		Minus<T>,
		Multiply<T>,
		Divide<T>,
		Modulo<T>
	{
		constexpr auto operator <=>(const Arithmetic&) const = default;
	};
}

#endif
