
//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_DEFINES_HPP
#define GEORITHM_DEFINES_HPP

#pragma once

#include <cstddef>

namespace georithm
{
	using DimensionDescriptor_t = std::size_t;
	using VertexIndex_t = std::size_t;
	using EdgeIndex_t = std::size_t;

	enum class LineType
	{
		line,
		ray,
		segment
	};

	enum class LineIntersectionResult
	{
		none,
		intersecting,
		parallel,
		collinear
	};
}

#endif
