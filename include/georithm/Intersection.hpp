
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

#include "Utility.hpp"
#include "Concepts.hpp"
#include "GeometricTraits.hpp"

namespace georithm::detail
{
	template <LineObject TLine>
	constexpr bool isWithinRange(const TLine& line, typename GeometricTraits<TLine>::ValueType dist) noexcept
	{
		if constexpr (TLine::Type == LineType::segment)
		{
			return 0 <= dist && dist < 1;
		}
		else if constexpr (TLine::Type == LineType::ray)
		{
			return 0 <= dist;
		}
		else
			return true;
	}

	template <NDimensionalLineObject<2> TLine1, NDimensionalLineObject<2> TLine2>
	constexpr std::tuple<LineIntersectionResult, typename GeometricTraits<TLine1>::ValueType> intersectionImpl(const TLine1& lhs, const TLine2& rhs) noexcept
	{
		assert(!isNull(lhs) && !isNull(rhs));

		auto lhsBegin = lhs.location();
		auto lhsDirection = lhs.direction();
		auto lhsLocalRhsBegin = rhs.location() - lhsBegin;
		auto rhsDirection = rhs.direction();

		auto denominator = lhsDirection[0] * rhsDirection[1] - lhsDirection[1] * rhsDirection[0];
		auto numeratorA = rhsDirection[0] * lhsLocalRhsBegin[1] - rhsDirection[1] * lhsLocalRhsBegin[0];
		auto numeratorB = lhsDirection[0] * lhsLocalRhsBegin[1] - lhsDirection[1] * lhsLocalRhsBegin[0];
		if (denominator == 0 && (numeratorA == 0 || numeratorB == 0))
			return { LineIntersectionResult::collinear, {} };

		if (denominator == 0)
			return { LineIntersectionResult::parallel, {} };

		if (auto result = numeratorA / denominator;
			isWithinRange(lhs, result) && isWithinRange(rhs, numeratorB / denominator))
		{
			return { LineIntersectionResult::intersecting, result };
		}
		return { LineIntersectionResult::none, {} };
	}

	template <NDimensionalLineObject<2> TLine, NDimensionalPolygonalObject<2> TPolygon, std::invocable<TLine, typename GeometricTraits<TLine>::ValueType> Callback>
	constexpr void forEachIntersectionImpl(const TLine& line, const TPolygon& polygon, Callback callback) noexcept
	{
		assert(!isNull(line) && !isNull(polygon));
		for (auto i = 0; i < edgeCount(polygon); ++i)
		{
			auto seg = edge(polygon, i);
			if (auto [intersectionResult, dist] = intersection(seg, line); intersectionResult == LineIntersectionResult::intersecting)
			{
				// ToDo: std::invoke(callback, dist)
				callback(seg, dist);
			}
		}
	}

	template <NDimensionalLineObject<2> TLine, NDimensionalPolygonalObject<2> TPolygon>
	constexpr std::optional<typename GeometricTraits<TLine>::ValueType> intersectionImpl(const TLine& line, const TPolygon& polygon) noexcept
	{
		assert(!isNull(line) && !isNull(polygon));

		using Value_t = typename GeometricTraits<TLine>::ValueType;
		std::optional<Value_t> smallestDist;
		forEachIntersectionImpl(line, polygon,
			[&smallestDist](const TLine& line, Value_t dist)
			{
				if (!smallestDist || std::abs(dist) < std::abs(*smallestDist))
					smallestDist = dist;
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
