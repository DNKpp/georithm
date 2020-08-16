//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_INTERSECTS_HPP
#define GEORITHM_INTERSECTS_HPP

#pragma once

#include <cassert>
#include <tuple>

#include "Concepts.hpp"
#include "Utility.hpp"

namespace georithm::detail
{
	template <LineObject TLine1, LineObject TLine2>
	requires EqualDimensions<TLine1, TLine2>
	constexpr bool intersectsImpl(const TLine1& lhs, const TLine2& rhs) noexcept
	{
		return std::get<0>(intersection(lhs, rhs)) == LineIntersectionResult::intersecting;
	}

	template <NDimensionalLineObject<2> TLine, NDimensionalPolygonalObject<2> TPoly>
	constexpr bool intersectsImpl(const TLine& line, const TPoly& polygon) noexcept
	{
		assert(!isNull(line) && !isNull(polygon));
		for (VertexIndex_t i = 0; i < edgeCount(polygon); ++i)
		{
			if (intersects(line, edge(polygon, i)))
				return true;
		}
		return false;
	}

	template <NDimensionalPolygonalObject<2> TPoly1, NDimensionalPolygonalObject<2> TPoly2>
	constexpr bool intersectsImpl(const TPoly1& lhs, const TPoly2& rhs) noexcept
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
	template <class TGeo1, class TGeo2>
	constexpr bool intersectsImpl(const TGeo1& lhs, const TGeo2& rhs) noexcept
	{
		return detail::intersectsImpl(rhs, lhs);
	}
}

namespace georithm
{
	template <GeometricObject TGeo1, GeometricObject TGeo2>
	requires EqualDimensions<TGeo1, TGeo2>
	constexpr bool intersects(const TGeo1& lhs, const TGeo2& rhs) noexcept
	{
		return detail::intersectsImpl(lhs, rhs);
	}
}

#endif
