//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_GEOMETRIC_TRAITS_HPP
#define GEORITHM_GEOMETRIC_TRAITS_HPP

#pragma once

#include <type_traits>

#include "georithm/BasicConcepts.hpp"
#include "georithm/Defines.hpp"

namespace georithm
{
	template <class TGeo>
	requires requires (const std::remove_cvref_t<TGeo>& object)
	{
		typename TGeo::VectorType;
	}
	struct GeometricTraits
	{
		using VectorType = typename TGeo::VectorType;
		using DimensionDescriptorType = typename VectorType::DimensionDescriptorType;
		using ValueType = typename VectorType::ValueType;

		constexpr static DimensionDescriptorType dimensions{ VectorType::dimensions };
	};
}

#endif
