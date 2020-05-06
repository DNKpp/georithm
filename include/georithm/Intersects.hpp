
//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_INTERSECTS_HPP
#define GEORITHM_INTERSECTS_HPP

#pragma once

#include <cassert>
#include <optional>

#include "Utility.hpp"
#include "Concepts.hpp"
#include "GeometricTraits.hpp"

namespace georithm::detail
{
	template <LineObject Line1, LineObject Line2>
	requires EqualDimensions<Line1, Line2>
	constexpr bool intersectsImpl(const Line1& lhs, const Line2& rhs) noexcept
	{
		return std::get<0>(intersection(lhs, rhs)) == LineIntersectionResult::intersecting;
	}

	template <NDimensionalLineObject<2> Line, NDimensionalPolygonalObject<2> Poly>
	constexpr bool intersectsImpl(const Line& line, const Poly& polygon) noexcept
	{
		assert(!isNull(line) && !isNull(polygon));
		for (VertexIndex_t i = 0; i < edgeCount(polygon); ++i)
		{
			if (intersects(line, edge(polygon, i)))
				return true;
		}
		return false;
	}

	template <NDimensionalPolygonalObject<2> Poly1, NDimensionalPolygonalObject<2> Poly2>
	constexpr bool intersectsImpl(const Poly1& lhs, const Poly2& rhs) noexcept
	{
		assert(!isNull(lhs) && !isNull(rhs));
		for (VertexIndex_t i = 0; i < edgeCount(lhs); ++i)
		{
			if (intersects(edge(lhs, i), rhs))
				return true;
		}
		return false;
	}

	// try to reverse the params
	template <class Geo1, class Geo2>
	constexpr bool intersectsImpl(const Geo1& lhs, const Geo2& rhs) noexcept
	{
		return detail::intersectsImpl(rhs, lhs);
	}
}

namespace georithm
{
	template <GeometricObject Geo1, GeometricObject Geo2>
	requires EqualDimensions<Geo1, Geo2>
	constexpr bool intersects(const Geo1& lhs, const Geo2& rhs) noexcept
	{
		return detail::intersectsImpl(lhs, rhs);
	}
}

#endif
