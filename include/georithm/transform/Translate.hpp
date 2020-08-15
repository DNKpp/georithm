//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_TRANSFORM_TRANSLATE_HPP
#define GEORITHM_TRANSFORM_TRANSLATE_HPP

#pragma once

#include "georithm/Concepts.hpp"

namespace georithm::transform
{
	template <VectorObject TVectorType>
	class Translate
	{
	public:
		using VectorType = TVectorType;
		using ValueType = typename TVectorType::ValueType;

		constexpr Translate() noexcept = default;
		/*ToDo: c++20
		constexpr */
		~Translate() noexcept = default;

		constexpr explicit Translate(const VectorType& translation) noexcept :
			m_Translation{ translation }
		{
		}

		constexpr Translate(const Translate&) = default;
		constexpr Translate& operator =(const Translate&) = default;
		constexpr Translate(Translate&&) = default;
		constexpr Translate& operator =(Translate&&) = default;

		[[nodiscard]] constexpr bool operator ==(const Translate&) const = default;

		[[nodiscard]] constexpr const VectorType& translation() const noexcept
		{
			return m_Translation;
		}

		[[nodiscard]] constexpr VectorType& translation() noexcept
		{
			return m_Translation;
		}

		[[nodiscard]] constexpr VectorType transform(VectorType vec) const noexcept
		{
			return vec += m_Translation;
		}

	private:
		VectorType m_Translation;
	};
}

#endif
