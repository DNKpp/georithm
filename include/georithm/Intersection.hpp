//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_INTERSECTION_HPP
#define GEORITHM_INTERSECTION_HPP

#pragma once

#include <cassert>
#include <optional>
#include <tuple>

#include "Concepts.hpp"
#include "GeometricTraits.hpp"
#include "Utility.hpp"

namespace georithm::detail
{
	template <LineObject TLine>
	constexpr bool isWithinRange(const TLine& line, typename GeometricTraits<TLine>::ValueType dist) noexcept
	{
		if constexpr (TLine::type == LineType::segment)
		{
			return 0 <= dist && dist <= 1;
		}
		else if constexpr (TLine::type == LineType::ray)
		{
			return 0 <= dist;
		}
		else
			return true;
	}

	template <NDimensionalLineObject<2> TLine1, NDimensionalLineObject<2> TLine2>
	constexpr std::tuple<LineIntersectionResult, typename GeometricTraits<TLine1>::ValueType, typename GeometricTraits<TLine2>::ValueType> intersectionImpl(
		const TLine1& lhs,
		const TLine2& rhs
	) noexcept
	{
		// Credits goes here: http://www-cs.ccny.cuny.edu/~wolberg/capstone/intersection/Intersection%20point%20of%20two%20lines.html
		assert(!isNull(lhs) && !isNull(rhs));

		auto lhsDirection = lhs.direction();
		auto rhsLocalLhsBegin = lhs.location() - rhs.location();
		auto rhsDirection = rhs.direction();

		auto denominator = rhsDirection[1] * lhsDirection[0] - rhsDirection[0] * lhsDirection[1];
		auto numeratorA = rhsDirection[0] * rhsLocalLhsBegin[1] - rhsDirection[1] * rhsLocalLhsBegin[0];
		auto numeratorB = lhsDirection[0] * rhsLocalLhsBegin[1] - lhsDirection[1] * rhsLocalLhsBegin[0];
		if (denominator == 0 && (numeratorA == 0 || numeratorB == 0))
			return { LineIntersectionResult::collinear, {}, {} };

		if (denominator == 0)
			return { LineIntersectionResult::parallel, {}, {} };

		auto resultLhs = numeratorA / denominator;
		auto resultRhs = numeratorB / denominator;
		if (isWithinRange(lhs, resultLhs) && isWithinRange(rhs, resultRhs))
		{
			return { LineIntersectionResult::intersecting, resultLhs, resultRhs };
		}
		return { LineIntersectionResult::none, {}, {} };
	}

	template <NDimensionalLineObject<2> TLine, NDimensionalPolygonalObject<2> TPolygon,
		std::invocable<typename GeometricTraits<TLine>::ValueType, TLine, typename GeometricTraits<TLine>::ValueType> Callback>
	constexpr void forEachIntersectionImpl(const TLine& line, const TPolygon& polygon, Callback callback) noexcept
	{
		assert(!isNull(line) && !isNull(polygon));
		for (auto i = 0; i < edgeCount(polygon); ++i)
		{
			auto seg = edge(polygon, i);
			if (auto [intersectionResult, lhsDist, rhsDist] = intersection(line, seg);
				intersectionResult == LineIntersectionResult::intersecting)
			{
				// ToDo: std::invoke(callback, dist)
				callback(lhsDist, seg, rhsDist);
			}
		}
	}

	template <NDimensionalLineObject<2> TLine, NDimensionalPolygonalObject<2> TPolygon>
	constexpr std::optional<typename GeometricTraits<TLine>::ValueType> intersectionImpl(
		const TLine& line,
		const TPolygon& polygon
	) noexcept
	{
		assert(!isNull(line) && !isNull(polygon));

		using Value_t = typename GeometricTraits<TLine>::ValueType;
		std::optional<Value_t> smallestDist;
		forEachIntersectionImpl(line,
								polygon,
								[&smallestDist](Value_t lineDist, const TLine& edge, Value_t edgeDist)
								{
									if (!smallestDist || std::abs(lineDist) < std::abs(*smallestDist))
										smallestDist = lineDist;
								}
								);
		return smallestDist;
	}

	// simply reverse params
	template <NDimensionalObject<2> TGeo, NDimensionalLineObject<2> TLine, class Callback>
	constexpr auto forEachIntersectionImpl(const TGeo& geo, const TLine& line, Callback callback) noexcept
	{
		return forEachIntersectionImpl(line, geo, callback);
	}

	// simply reverse params
	template <NDimensionalObject<2> TGeo, NDimensionalLineObject<2> TLine>
	constexpr auto intersectionImpl(const TGeo& geo, const TLine& line) noexcept
	{
		return intersectionImpl(line, geo);
	}
}

namespace georithm
{
	template <GeometricObject TGeo1, GeometricObject TGeo2>
	requires EqualDimensions<TGeo1, TGeo2>
	constexpr auto intersection(const TGeo1& lhs, const TGeo2& rhs) noexcept
	{
		return detail::intersectionImpl(lhs, rhs);
	}

	template <GeometricObject TGeo1, GeometricObject TGeo2, class Callback>
	requires EqualDimensions<TGeo1, TGeo2>
	constexpr auto forEachIntersection(const TGeo1& lhs, const TGeo2& rhs, Callback callback) noexcept
	{
		return detail::forEachIntersectionImpl(lhs, rhs, callback);
	}
}

#endif
