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
	[[nodiscard]] constexpr T leftBounding(const AABB_t<T>& rect) noexcept
	{
		assert(!isNull(rect));
		return std::min(rect.position().x(), rect.position().x() + rect.span().x());
	}

	template <class T>
	[[nodiscard]] constexpr T rightBounding(const AABB_t<T>& rect) noexcept
	{
		assert(!isNull(rect));
		return std::max(rect.position().x(), rect.position().x() + rect.span().x());
	}

	template <class T>
	[[nodiscard]] constexpr T topBounding(const AABB_t<T>& rect) noexcept
	{
		assert(!isNull(rect));
		return std::min(rect.position().y(), rect.position().y() + rect.span().y());
	}

	template <class T>
	[[nodiscard]] constexpr T bottomBounding(const AABB_t<T>& rect) noexcept
	{
		assert(!isNull(rect));
		return std::max(rect.position().y(), rect.position().y() + rect.span().y());
	}

	template <NDimensionalPolygonalObject<2> TPolygon>
	[[nodiscard]] constexpr typename GeometricTraits<TPolygon>::ValueType leftBounding(const TPolygon& polygon) noexcept
	{
		auto count = vertexCount(polygon);
		assert(!isNull(polygon) && 2 < count);
		auto min = vertex(polygon, 0).x();

		for (VertexIndex_t i = 1; i < count; ++i)
			min = std::min(min, vertex(polygon, i).x());
		return min;
	}

	template <NDimensionalPolygonalObject<2> TPolygon>
	[[nodiscard]] constexpr typename GeometricTraits<TPolygon>::ValueType topBounding(const TPolygon& polygon) noexcept
	{
		auto count = vertexCount(polygon);
		assert(!isNull(polygon) && 2 < count);
		auto min = vertex(polygon, 0).y();

		for (VertexIndex_t i = 1; i < count; ++i)
			min = std::min(min, vertex(polygon, i).y());
		return min;
	}

	template <NDimensionalPolygonalObject<2> TPolygon>
	[[nodiscard]] constexpr typename GeometricTraits<TPolygon>::ValueType rightBounding(const TPolygon& polygon) noexcept
	{
		auto count = vertexCount(polygon);
		assert(!isNull(polygon) && 2 < count);
		auto max = vertex(polygon, 0).x();

		for (VertexIndex_t i = 1; i < count; ++i)
			max = std::max(max, vertex(polygon, i).x());
		return max;
	}

	template <NDimensionalPolygonalObject<2> TPolygon>
	[[nodiscard]] constexpr typename GeometricTraits<TPolygon>::ValueType bottomBounding(const TPolygon& polygon) noexcept
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

		Vector position{ leftBounding(polygon), topBounding(polygon) };
		return { position, Vector{ rightBounding(polygon), bottomBounding(polygon) } - position };
	}
}

namespace georithm
{
	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::ValueType leftBounding(const TObj& rect) noexcept
	{
		return detail::leftBounding(rect);
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::ValueType rightBounding(const TObj& rect) noexcept
	{
		return detail::rightBounding(rect);
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::ValueType topBounding(const TObj& rect) noexcept
	{
		return detail::topBounding(rect);
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::ValueType bottomBounding(const TObj& rect) noexcept
	{
		return detail::bottomBounding(rect);
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr AABB_t<typename GeometricTraits<TObj>::ValueType> makeBoundingRect(const TObj& object) noexcept
	{
		return detail::makeBoundingRect(object);
	}
}

#endif
