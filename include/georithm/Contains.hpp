
//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_CONTAINS_HPP
#define GEORITHM_CONTAINS_HPP

#pragma once

#include <cassert>

#include "Utility.hpp"
#include "Concepts.hpp"
#include "GeometricTraits.hpp"
#include "Intersection.hpp"

namespace georithm::detail
{
	template <NDimensionalPolygonalObject<2> TPolygon, NDimensionalVectorObject<2> TVector>
	constexpr bool containsImpl(const TPolygon& polygon, const TVector& vector) noexcept
	{
		assert(!isNull(polygon));

		using Traits_t = GeometricTraits<TPolygon>;
		using Vector_t = typename Traits_t::VectorType;
		using Value_t = typename Traits_t::ValueType;
		Ray<Vector_t> ray{ vector, { Value_t(1), Value_t(0) } };

		int count = 0;
		//for (VertexIndex_t i = 0; i < vertexCount(polygon); ++i)
		//{
		//	auto segment = edge(polygon, i);
		//	auto [result, dist] = intersection(ray, segment);
		//	using enum LineIntersectionResult;
		//	switch (result)
		//	{
		//	case intersecting:
		//		++count;
		//		break;
		//	case collinear:
		//	{
		//		auto sqLength = lengthSq(vector - segment.firstVertex());
		//		if (0 <= sqLength && sqLength < lengthSq(segment.direction()))
		//			++count;
		//	}
		//	}
		//}
		forEachIntersection(polygon, ray,
			[&count](const auto& line, auto dist) { ++count; }
		);
		
		return count % 2 == 1;
	}

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
	template <GeometricObject Geo1, class T>
	constexpr bool contains(const Geo1& lhs, const T& rhs) noexcept
	{
		return detail::containsImpl(lhs, rhs);
	}
}

#endif
