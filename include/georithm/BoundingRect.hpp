
//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_BOUNDING_RECT_HPP
#define GEORITHM_BOUNDING_RECT_HPP

#pragma once

#include "Concepts.hpp"
#include "Defines.hpp"
#include "GeometricTraits.hpp"
#include "Rect.hpp"
#include "Utility.hpp"
#include "component/Translation.hpp"

namespace georithm::detail
{
	template <NDimensionalVectorObject<2> TVector>
	using AABB_t = typename Rect<TVector, typename component::Translation<TVector>>;

	template <NDimensionalPolygonalObject<2> Poly>
	constexpr AABB_t<typename GeometricTraits<Poly>::VectorType> makeBoundingRectImpl(const Poly& polygon) noexcept
	{
		assert(!isNull(polygon) && 2 <= vertexCount(polygon));

		using Vector_t = typename GeometricTraits<Poly>::VectorType;
		using NumericLimits_t = std::numeric_limits<typename Vector_t::ValueType>;
		Vector_t topLeft{ NumericLimits_t::max(), NumericLimits_t::max() };
		Vector_t bottomRight{ NumericLimits_t::min(), NumericLimits_t::min() };

		for (VertexIndex_t i = 0; i < vertexCount(polygon); ++i)
		{
			auto v = vertex(polygon, i);
			topLeft[0] = std::min(topLeft[0], v[0]);
			topLeft[1] = std::min(topLeft[1], v[1]);
			bottomRight[0] = std::max(bottomRight[0], v[0]);
			bottomRight[1] = std::max(bottomRight[1], v[1]);
		}

		assert(topLeft[0] <= bottomRight[0] && topLeft[1] <= bottomRight[1]);
		return { bottomRight - topLeft, topLeft };
	}
}

namespace georithm
{
	template <NDimensionalObject<2> Geo>
	constexpr auto makeBoundingRect(const Geo& object) noexcept
	{
		return detail::makeBoundingRectImpl(object);
	}
}

#endif
