//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_TRANSFORM_SHEAR_HPP
#define GEORITHM_TRANSFORM_SHEAR_HPP

#pragma once

#include "georithm/Concepts.hpp"

namespace georithm::transform
{
	template <NDimensionalVectorObject<2> TVectorType>
	class Shear
	{
	public:
		using VectorType = TVectorType;
		using ValueType = typename TVectorType::ValueType;

		constexpr Shear() noexcept = default;
		/*ToDo: c++20
		constexpr */
		~Shear() noexcept = default;

		constexpr explicit Shear(const VectorType& shear) noexcept :
			m_Shear{ shear }
		{
		}

		constexpr Shear(const Shear&) = default;
		constexpr Shear& operator =(const Shear&) = default;
		constexpr Shear(Shear&&) = default;
		constexpr Shear& operator =(Shear&&) = default;

		[[nodiscard]] constexpr bool operator ==(const Shear&) const = default;

		[[nodiscard]] constexpr const VectorType& shear() const noexcept
		{
			return m_Shear;
		}

		[[nodiscard]] constexpr VectorType& shear() noexcept
		{
			return m_Shear;
		}

		[[nodiscard]] constexpr VectorType transform(const VectorType& vec) const noexcept
		{
			return { vec.x() + m_Shear.x() * vec.y(), vec.y() + m_Shear.y() * vec.x() };
		}

	private:
		VectorType m_Shear;
	};
}

#endif
