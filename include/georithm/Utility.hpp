//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_UTILITY_HPP
#define GEORITHM_UTILITY_HPP

#pragma once

#include <cassert>
#include <concepts>

#include "georithm/Concepts.hpp"
#include "georithm/Defines.hpp"

namespace georithm
{
	template <class T>
	[[nodiscard]] constexpr bool isNull(const T& object) noexcept
	requires requires { { object.isNull() }->std::convertible_to<bool>; }
	{
		return object.isNull();
	}

	template <class T>
	[[nodiscard]] constexpr VertexIndex_t vertexCount(const T& object) noexcept
	requires requires { { object.vertexCount() }->std::convertible_to<VertexIndex_t>; }
	{
		return object.vertexCount();
	}

	template <class T>
	[[nodiscard]] constexpr EdgeIndex_t edgeCount(const T& object) noexcept
	requires requires { { object.edgeCount() }->std::convertible_to<EdgeIndex_t>; }
	{
		return object.edgeCount();
	}

	template <class T>
	[[nodiscard]] constexpr auto vertex(const T& object, VertexIndex_t index) noexcept -> decltype(object.vertex(index))
	requires requires
	{
		{ object.vertex(index) } -> VectorObject;
	}
	{
		return object.vertex(index);
	}

	template <class T>
	[[nodiscard]] constexpr auto edge(const T& object, EdgeIndex_t index) noexcept -> decltype(object.edge(index))
	requires requires
	{
		{ object.edge(index) }->LineObject;
	}
	{
		return object.edge(index);
	}
}

#endif
