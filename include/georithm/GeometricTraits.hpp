
//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_GEOMETRIC_TRAITS_HPP
#define GEORITHM_GEOMETRIC_TRAITS_HPP

#pragma once

#include "Defines.hpp"

namespace georithm
{
	template <class TGeo>
	struct GeometricTraits
	{
		using VectorType = typename TGeo::VectorType;
		using DimensionDescriptorType = typename VectorType::DimensionDescriptorType;
		using ValueType = typename VectorType::ValueType;

		constexpr static DimensionDescriptorType Dimensions{ VectorType::Dimensions };
	};
}

#endif
