//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_BOUNDING_RECT_HPP
#define GEORITHM_BOUNDING_RECT_HPP

#pragma once

#include <algorithm>
#include <limits>

#include "Concepts.hpp"
#include "Defines.hpp"
#include "GeometricTraits.hpp"
#include "Rect.hpp"
#include "Utility.hpp"
#include "Vector.hpp"

namespace georithm::detail
{
	template <class T>
	[[nodiscard]] constexpr T left(const AABB_t<T>& rect) noexcept
	{
		assert(!isNull(rect));
		return std::min(rect.position().x(), rect.position().x() + rect.span().x());
	}

	template <class T>
	[[nodiscard]] constexpr T right(const AABB_t<T>& rect) noexcept
	{
		assert(!isNull(rect));
		return std::max(rect.position().x(), rect.position().x() + rect.span().x());
	}

	template <class T>
	[[nodiscard]] constexpr T top(const AABB_t<T>& rect) noexcept
	{
		assert(!isNull(rect));
		return std::min(rect.position().y(), rect.position().y() + rect.span().y());
	}

	template <class T>
	[[nodiscard]] constexpr T bottom(const AABB_t<T>& rect) noexcept
	{
		assert(!isNull(rect));
		return std::max(rect.position().y(), rect.position().y() + rect.span().y());
	}

	template <NDimensionalPolygonalObject<2> TPolygon>
	[[nodiscard]] constexpr typename GeometricTraits<TPolygon>::ValueType left(const TPolygon& polygon) noexcept
	{
		auto count = vertexCount(polygon);
		assert(!isNull(polygon) && 2 < count);
		auto min = vertex(polygon, 0).x();

		for (VertexIndex_t i = 1; i < count; ++i)
			min = std::min(min, vertex(polygon, i).x());
		return min;
	}

	template <NDimensionalPolygonalObject<2> TPolygon>
	[[nodiscard]] constexpr typename GeometricTraits<TPolygon>::ValueType top(const TPolygon& polygon) noexcept
	{
		auto count = vertexCount(polygon);
		assert(!isNull(polygon) && 2 < count);
		auto min = vertex(polygon, 0).y();

		for (VertexIndex_t i = 1; i < count; ++i)
			min = std::min(min, vertex(polygon, i).y());
		return min;
	}

	template <NDimensionalPolygonalObject<2> TPolygon>
	[[nodiscard]] constexpr typename GeometricTraits<TPolygon>::ValueType right(const TPolygon& polygon) noexcept
	{
		auto count = vertexCount(polygon);
		assert(!isNull(polygon) && 2 < count);
		auto max = vertex(polygon, 0).x();

		for (VertexIndex_t i = 1; i < count; ++i)
			max = std::max(max, vertex(polygon, i).x());
		return max;
	}

	template <NDimensionalPolygonalObject<2> TPolygon>
	[[nodiscard]] constexpr typename GeometricTraits<TPolygon>::ValueType bottom(const TPolygon& polygon) noexcept
	{
		auto count = vertexCount(polygon);
		assert(!isNull(polygon) && 2 < count);
		auto max = vertex(polygon, 0).y();

		for (VertexIndex_t i = 1; i < count; ++i)
			max = std::max(max, vertex(polygon, i).y());
		return max;
	}

	template <NDimensionalPolygonalObject<2> TPolygon>
	[[nodiscard]] constexpr AABB_t<typename GeometricTraits<TPolygon>::ValueType> makeBoundingRect(const TPolygon& polygon) noexcept
	{
		assert(!isNull(polygon) && 2 <= vertexCount(polygon));

		Vector position{ left(polygon), top(polygon) };
		return { position, Vector{ right(polygon), bottom(polygon) } - position };
	}
}

namespace georithm
{
	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::ValueType left(const TObj& rect) noexcept
	{
		return detail::left(rect);
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::ValueType right(const TObj& rect) noexcept
	{
		return detail::right(rect);
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::ValueType top(const TObj& rect) noexcept
	{
		return detail::top(rect);
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::ValueType bottom(const TObj& rect) noexcept
	{
		return detail::bottom(rect);
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr AABB_t<typename GeometricTraits<TObj>::ValueType> makeBoundingRect(const TObj& object) noexcept
	{
		return detail::makeBoundingRect(object);
	}
}

#endif
