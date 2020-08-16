//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_CONTAINS_HPP
#define GEORITHM_CONTAINS_HPP

#pragma once

#include <cassert>

#include "georithm/Bounding.hpp"
#include "georithm/Concepts.hpp"
#include "georithm/GeometricTraits.hpp"
#include "georithm/Rect.hpp"
#include "georithm/Utility.hpp"

namespace georithm::detail
{
	// not sure if this would be right to expose to the general georithm namespace; possibly to concrete
	template <class T>
	struct IsRect :
		std::false_type
	{
	};

	template <class T, class... TTransformer>
	struct IsRect<Rect<T, TTransformer...>> :
		std::true_type
	{
	};

	template <class T>
	constexpr bool IsRect_v = IsRect<T>::value;

	template <class T>
	concept RectType = NDimensionalPolygonalObject<T, 2> && IsRect_v<T>;

	template <class T, NDimensionalVectorObject<2> TVector>
	requires std::is_same_v<T, typename TVector::ValueType>
	[[nodiscard]] constexpr bool contains(const AABB_t<T>& rect, const TVector& point) noexcept
	{
		assert(!isNull(rect));
		return leftBounding(rect) <= point.x() && point.x() <= rightBounding(rect) && topBounding(rect) <= point.y() && point.y() <= bottomBounding(rect);
	}

	template <class T>
	[[nodiscard]] constexpr bool contains(const AABB_t<T>& outerRect, const AABB_t<T>& innerRect) noexcept
	{
		assert(!isNull(outerRect) && !isNull(innerRect));

		auto outerTopLeft = topLeftBounding(outerRect);
		auto innerTopLeft = topLeftBounding(innerRect);
		auto outerBottomRight = bottomRightBounding(outerRect);
		auto innerBottomRight = topLeftBounding(outerRect);
		return outerTopLeft.x() <= innerTopLeft.x() && outerTopLeft.y() <= innerTopLeft.y() &&
			innerBottomRight.x() <= outerBottomRight.x() && innerBottomRight.y() <= outerBottomRight.y();
	}

	template <RectType TRect, NDimensionalVectorObject<2> TVector>
	requires (0 < TRect::transformerCount) && std::is_same_v<typename GeometricTraits<TRect>::ValueType, typename TVector::ValueType>
	[[nodiscard]] constexpr bool contains(const TRect& rect, const TVector& point) noexcept
	{
		assert(!isNull(rect));

		// thanks to this post: https://math.stackexchange.com/a/190373
		// ToDo: potential issue here if vertex index gets changed... Think about a better solution
		auto vertex0 = vertex(rect, 0);
		auto AM = point - vertex0;
		auto AB = vertex(rect, 1) - vertex0;
		auto AD = vertex(rect, 3) - vertex0;

		auto scalar1 = scalarProduct(AM, AB);
		auto scalar2 = scalarProduct(AB, AB);
		auto scalar3 = scalarProduct(AM, AD);
		auto scalar4 = scalarProduct(AD, AD);

		return 0 <= scalar1 && scalar1 <= scalar2 && 0 <= scalar3 && scalar3 <= scalar4;
	}

	template <RectType TRect, NDimensionalPolygonalObject<2> TPolygon>
	requires (0 < TRect::transformerCount) && std::is_same_v<typename GeometricTraits<TRect>::ValueType, typename GeometricTraits<TPolygon>::ValueType>
	[[nodiscard]] constexpr bool contains(const TRect& outerRect, const TPolygon& innerPolygon) noexcept
	{
		assert(!isNull(outerRect) && !isNull(innerPolygon));

		for (VertexIndex_t i = 0, count = vertexCount(innerPolygon); i < count; ++i)
		{
			if (!contains(outerRect, vertex(innerPolygon, i)))
				return false;
		}
		return true;
	}

	//template <NDimensionalPolygonalObject<2> TPolygon, NDimensionalVectorObject<2> TVector>
	//requires (!IsRect_v<TPolygon>)
	//constexpr bool contains(const TPolygon& polygon, const TVector& vector) noexcept
	//{
	//	assert(!isNull(polygon));

	//	using Traits_t = GeometricTraits<TPolygon>;
	//	using Vector_t = typename Traits_t::VectorType;
	//	using Value_t = typename Traits_t::ValueType;
	//	Ray<Vector_t> ray{ vector, { Value_t(1), Value_t(0) } };

	//	auto count = 0;
	//	//for (VertexIndex_t i = 0; i < vertexCount(polygon); ++i)
	//	//{
	//	//	auto segment = edge(polygon, i);
	//	//	auto [result, dist] = intersection(ray, segment);
	//	//	using enum LineIntersectionResult;
	//	//	switch (result)
	//	//	{
	//	//	case intersecting:
	//	//		++count;
	//	//		break;
	//	//	case collinear:
	//	//	{
	//	//		auto sqLength = lengthSq(vector - segment.firstVertex());
	//	//		if (0 <= sqLength && sqLength < lengthSq(segment.direction()))
	//	//			++count;
	//	//	}
	//	//	}
	//	//}
	//	forEachIntersection(ray, polygon,
	//						[&count](auto rayDist, const auto& edge, auto edgeDist)
	//						{
	//							if (0 < rayDist)
	//								++count;
	//						}
	//	);

	//	return (count & 1) != 0;
	//}

	//template <NDimensionalPolygonalObject<2> Poly, NDimensionalLineObject<2> Line>
	//constexpr bool intersectsImpl(const Poly& polygon, const Line& line) noexcept
	//{
	//	assert(!isNull(line) && !isNull(polygon));
	//	for (VertexIndex_t i = 0; i < edgeCount(polygon); ++i)
	//	{
	//		if (intersects(line, edge(polygon, i)))
	//			return true;
	//	}
	//	return false;
	//}

	//template <NDimensionalPolygonalObject<2> Poly1, NDimensionalPolygonalObject<2> Poly2>
	//constexpr bool intersectsImpl(const Poly1& lhs, const Poly2& rhs) noexcept
	//{
	//	assert(!isNull(lhs) && !isNull(rhs));
	//	for (VertexIndex_t i = 0; i < edgeCount(lhs); ++i)
	//	{
	//		if (intersects(edge(lhs, i), rhs))
	//			return true;
	//	}
	//	return false;
	//}
}

namespace georithm
{
	template <GeometricObject TGeo1, class T>
	[[nodiscard]] constexpr bool contains(const TGeo1& lhs, const T& rhs) noexcept
	{
		return detail::contains(lhs, rhs);
	}
}

#endif
