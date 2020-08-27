//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_OVERLAPS_HPP
#define GEORITHM_OVERLAPS_HPP

#pragma once

#include <cassert>

#include "georithm/Concepts.hpp"
#include "georithm/Intersects.hpp"
#include "georithm/Contains.hpp"

namespace georithm::detail
{
	template <NDimensionalObject<2> TGeo1, NDimensionalObject<2> TGeo2>
	constexpr bool overlaps(const TGeo1& lhs, const TGeo2& rhs) noexcept
	{
		assert(!isNull(lhs) && !isNull(rhs));
		return intersects(lhs, rhs) || contains(lhs, rhs) || contains(rhs, lhs);
	}
}

namespace georithm
{
	template <NDimensionalObject<2> TGeo1, NDimensionalObject<2> TGeo2>
	[[nodiscard]] constexpr bool overlaps(const TGeo1& lhs, const TGeo2& rhs) noexcept
	{
		return detail::overlaps(lhs, rhs);
	}
}

#endif
