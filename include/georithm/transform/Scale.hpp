//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_TRANSFORM_SCALE_HPP
#define GEORITHM_TRANSFORM_SCALE_HPP

#pragma once

#include "georithm/Concepts.hpp"
#include "georithm/RangeAlgorithms.hpp"

namespace georithm::transform
{
	template <VectorObject TVectorType>
	class Scale
	{
	public:
		using VectorType = TVectorType;

		constexpr Scale() noexcept = default;
		/*ToDo: c++20
		constexpr */
		~Scale() noexcept = default;

		template <std::convertible_to<VectorType> T>
		explicit constexpr Scale(T&& translation) noexcept :
			m_Scale{ std::forward<T>(translation) }
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

	protected:
		[[nodiscard]] constexpr VectorType transform(VectorType vec) const noexcept
		{
			zip_elements(std::begin(vec), std::end(vec), std::begin(m_Scale),
						[](auto lhs, const auto& rhs) { return lhs * rhs; }
						);
			return vec;
		}

	private:
		VectorType m_Scale{ VectorType::ValueType(1), VectorType::ValueType(1) };
	};
}

#endif
