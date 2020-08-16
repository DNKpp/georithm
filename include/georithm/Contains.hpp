//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_CONTAINS_HPP
#define GEORITHM_CONTAINS_HPP

#pragma once

#include <cassert>

#include "Bounding.hpp"
#include "Concepts.hpp"
#include "GeometricTraits.hpp"
#include "Rect.hpp"
#include "Utility.hpp"

namespace georithm::detail
{
	//template <class TRect, NDimensionalVectorObject<2> TVector>
	//requires IsRect_v<TRect>
	//constexpr bool containsImpl(const TRect& rect, const TVector& vector) noexcept
	//{
	//	assert(!isNull(rect));

	//	// thanks to this post: https://math.stackexchange.com/a/190373
	//	auto vertex0 = vertex(rect, 0);
	//	auto AM = vector - vertex0;
	//	auto AB = vertex(rect, 1) - vertex0;
	//	auto AD = vertex(rect, 3) - vertex0;

	//	auto scalar1 = scalarProduct(AM, AB);
	//	auto scalar2 = scalarProduct(AB, AB);
	//	auto scalar3 = scalarProduct(AM, AD);
	//	auto scalar4 = scalarProduct(AD, AD);

	//	return 0 <= scalar1 && scalar1 <= scalar2 && 0 <= scalar3 && scalar3 <= scalar4;
	//}

	template <class T, NDimensionalVectorObject<2> TVector>
	requires std::convertible_to<T, typename TVector::ValueType>
	constexpr bool containsImpl(const AABB_t<T>& rect, const TVector& point) noexcept
	{
		assert(!isNull(rect));
		return leftBounding(rect) <= point.x() && point.x() <= rightBounding(rect) && topBounding(rect) <= point.y() && point.y() <= bottomBounding(rect);
	}

	//template <NDimensionalPolygonalObject<2> TPolygon, NDimensionalVectorObject<2> TVector>
	//requires (!IsRect_v<TPolygon>)
	//constexpr bool containsImpl(const TPolygon& polygon, const TVector& vector) noexcept
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
	constexpr bool contains(const TGeo1& lhs, const T& rhs) noexcept
	{
		return detail::containsImpl(lhs, rhs);
	}
}

#endif
