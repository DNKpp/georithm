//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_TRANSFORM_SCALE_HPP
#define GEORITHM_TRANSFORM_SCALE_HPP

#pragma once

#include "georithm/Concepts.hpp"

namespace georithm::transform
{
	template <VectorObject TVectorType>
	class Scale
	{
	public:
		using VectorType = TVectorType;
		using ValueType = typename TVectorType::ValueType;

		constexpr Scale() noexcept = default;
		/*ToDo: c++20
		constexpr */
		~Scale() noexcept = default;

		constexpr explicit Scale(const VectorType& scale) noexcept :
			m_Scale{ scale }
		{
		}

		constexpr Scale(const Scale&) = default;
		constexpr Scale& operator =(const Scale&) = default;
		constexpr Scale(Scale&&) = default;
		constexpr Scale& operator =(Scale&&) = default;

		[[nodiscard]] constexpr bool operator ==(const Scale&) const = default;

		[[nodiscard]] constexpr const VectorType& scale() const noexcept
		{
			return m_Scale;
		}

		[[nodiscard]] constexpr VectorType& scale() noexcept
		{
			return m_Scale;
		}

		[[nodiscard]] constexpr VectorType transform(VectorType vec) const noexcept
		{
			std::transform(std::cbegin(vec),
							std::cend(vec),
							std::cbegin(m_Scale),
							std::begin(vec),
							[](const auto& lhs, const auto& rhs) { return lhs * rhs; }
						);
			return vec;
		}

	private:
		VectorType m_Scale{ ValueType(1), ValueType(1) };
	};
}

#endif
