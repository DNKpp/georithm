//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_BOUNDING_RECT_HPP
#define GEORITHM_BOUNDING_RECT_HPP

#pragma once

#include <algorithm>

#include "georithm/Concepts.hpp"
#include "georithm/Defines.hpp"
#include "georithm/GeometricTraits.hpp"
#include "georithm/Rect.hpp"
#include "georithm/Utility.hpp"
#include "georithm/Vector.hpp"

namespace georithm::detail
{
	/*#####
	 * AABB overloads
	 *#####*/
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

	template <class T>
	[[nodiscard]] constexpr Vector<T, 2> topLeftBounding(const AABB_t<T>& rect) noexcept
	{
		assert(!isNull(rect));
		auto globalSecPos = rect.position() + rect.span();
		return { std::min(rect.position().x(), globalSecPos.x()), std::min(rect.position().y(), globalSecPos.y()) };
	}

	template <class T>
	[[nodiscard]] constexpr Vector<T, 2> topRightBounding(const AABB_t<T>& rect) noexcept
	{
		assert(!isNull(rect));
		auto globalSecPos = rect.position() + rect.span();
		return { std::max(rect.position().x(), globalSecPos.x()), std::min(rect.position().y(), globalSecPos.y()) };
	}

	template <class T>
	[[nodiscard]] constexpr Vector<T, 2> bottomLeftBounding(const AABB_t<T>& rect) noexcept
	{
		assert(!isNull(rect));
		auto globalSecPos = rect.position() + rect.span();
		return { std::min(rect.position().x(), globalSecPos.x()), std::max(rect.position().y(), globalSecPos.y()) };
	}

	template <class T>
	[[nodiscard]] constexpr Vector<T, 2> bottomRightBounding(const AABB_t<T>& rect) noexcept
	{
		assert(!isNull(rect));
		auto globalSecPos = rect.position() + rect.span();
		return { std::max(rect.position().x(), globalSecPos.x()), std::max(rect.position().y(), globalSecPos.y()) };
	}

	// is necessary because of the NDimensionalPolygonalObject overload
	template <class T>
	[[nodiscard]] constexpr AABB_t<T> boundingRect(const AABB_t<T>& rect) noexcept
	{
		assert(!isNull(rect));
		auto globalSecPos = rect.position() + rect.span();
		Vector<T, 2> topLeft{ std::min(rect.position().x(), globalSecPos.x()), std::min(rect.position().y(), globalSecPos.y()) };
		Vector<T, 2> bottomRight{ std::max(rect.position().x(), globalSecPos.x()), std::max(rect.position().y(), globalSecPos.y()) };
		return { topLeft, bottomRight - topLeft };
	}

	/*#####
	 * generic polygon overloads
	 *#####*/
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

	template <NDimensionalPolygonalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::VectorType topLeftBounding(const TObj& polygon) noexcept
	{
		auto count = vertexCount(polygon);
		assert(!isNull(polygon) && 2 < count);
		auto curVertex = vertex(polygon, 0);
		auto xMin = curVertex.x();
		auto yMin = curVertex.y();

		for (VertexIndex_t i = 1; i < count; ++i)
		{
			curVertex = vertex(polygon, i);
			xMin = std::min(xMin, curVertex.x());
			yMin = std::min(yMin, curVertex.y());
		}
		return { xMin, yMin };
	}

	template <NDimensionalPolygonalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::VectorType topRightBounding(const TObj& polygon) noexcept
	{
		auto count = vertexCount(polygon);
		assert(!isNull(polygon) && 2 < count);
		auto curVertex = vertex(polygon, 0);
		auto xMax = curVertex.x();
		auto yMin = curVertex.y();

		for (VertexIndex_t i = 1; i < count; ++i)
		{
			curVertex = vertex(polygon, i);
			xMax = std::max(xMax, curVertex.x());
			yMin = std::min(yMin, curVertex.y());
		}
		return { xMax, yMin };
	}

	template <NDimensionalPolygonalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::VectorType bottomLeftBounding(const TObj& polygon) noexcept
	{
		auto count = vertexCount(polygon);
		assert(!isNull(polygon) && 2 < count);
		auto curVertex = vertex(polygon, 0);
		auto xMin = curVertex.x();
		auto yMax = curVertex.y();

		for (VertexIndex_t i = 1; i < count; ++i)
		{
			curVertex = vertex(polygon, i);
			xMin = std::min(xMin, curVertex.x());
			yMax = std::max(yMax, curVertex.y());
		}
		return { xMin, yMax };
	}

	template <NDimensionalPolygonalObject<2> TPolygon>
	[[nodiscard]] constexpr AABB_t<typename GeometricTraits<TPolygon>::ValueType> boundingRect(const TPolygon& polygon) noexcept
	{
		auto count = vertexCount(polygon);
		assert(!isNull(polygon) && 2 < count);
		auto curVertex = vertex(polygon, 0);
		auto xMin = curVertex.x();
		auto yMin = curVertex.y();
		auto xMax = curVertex.x();
		auto yMax = curVertex.y();

		for (VertexIndex_t i = 1; i < count; ++i)
		{
			curVertex = vertex(polygon, i);
			xMin = std::min(xMin, curVertex.x());
			yMin = std::min(yMin, curVertex.y());
			xMax = std::max(xMax, curVertex.x());
			yMax = std::max(yMax, curVertex.y());
		}
		Vector position{ xMin, yMin };
		return { position, Vector{ xMax, yMax } - position };
	}

	/*#####
	 * generic object overloads
	 *#####*/
	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::VectorType topLeftBounding(const TObj& obj) noexcept
	{
		return { leftBounding(obj), topBounding(obj) };
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::VectorType topRightBounding(const TObj& obj) noexcept
	{
		return { rightBounding(obj), topBounding(obj) };
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::VectorType bottomLeftBounding(const TObj& obj) noexcept
	{
		return { leftBounding(obj), bottomBounding(obj) };
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::VectorType bottomRightBounding(const TObj& obj) noexcept
	{
		return { rightBounding(obj), bottomBounding(obj) };
	}

	template <NDimensionalObject<2> TObject>
	[[nodiscard]] constexpr AABB_t<typename GeometricTraits<TObject>::ValueType> boundingRect(const TObject& object) noexcept
	{
		assert(!isNull(object) && 2 <= vertexCount(object));

		auto position = topLeftBounding(object);
		return { position, bottomRightBounding(object) - position };
	}

	template <NDimensionalVectorObject<2> TVector>
	[[nodiscard]] constexpr AABB_t<typename TVector::ValueType> boundingRect(const TVector& vector1, const TVector& vector2) noexcept
	{
		return { transmuteElementWise(vector1, vector2, [](const auto& lhs, const auto& rhs) { return std::min(lhs, rhs); }), abs(vector1 - vector2) };
	}
}

namespace georithm
{
	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::ValueType leftBounding(const TObj& obj) noexcept
	{
		return detail::leftBounding(obj);
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::ValueType rightBounding(const TObj& obj) noexcept
	{
		return detail::rightBounding(obj);
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::ValueType topBounding(const TObj& obj) noexcept
	{
		return detail::topBounding(obj);
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::ValueType bottomBounding(const TObj& obj) noexcept
	{
		return detail::bottomBounding(obj);
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::VectorType topLeftBounding(const TObj& obj) noexcept
	{
		return detail::topLeftBounding(obj);
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::VectorType topRightBounding(const TObj& obj) noexcept
	{
		return detail::topRightBounding(obj);
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::VectorType bottomLeftBounding(const TObj& obj) noexcept
	{
		return detail::bottomLeftBounding(obj);
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr typename GeometricTraits<TObj>::VectorType bottomRightBounding(const TObj& obj) noexcept
	{
		return detail::bottomRightBounding(obj);
	}

	template <NDimensionalObject<2> TObj>
	[[nodiscard]] constexpr AABB_t<typename GeometricTraits<TObj>::ValueType> boundingRect(const TObj& object) noexcept
	{
		return detail::boundingRect(object);
	}

	template <NDimensionalVectorObject<2> TVector>
	[[nodiscard]] constexpr AABB_t<typename TVector::ValueType> boundingRect(const TVector& vector1, const TVector& vector2) noexcept
	{
		return detail::boundingRect(vector1, vector2);
	}
}

#endif
