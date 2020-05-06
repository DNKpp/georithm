
//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_COMPONENT_TRANSLATION_HPP
#define GEORITHM_COMPONENT_TRANSLATION_HPP

#pragma once

namespace georithm::component
{
	template<class TVectorType>
	class Translation
	{
	public:
		using VectorType = TVectorType;

		constexpr Translation() noexcept = default;

		template <std::convertible_to<TVectorType> T>
		constexpr Translation(T&& translation) noexcept :
			m_Translation(std::forward<T>(translation))
		{}

		constexpr Translation(const Translation&) = default;
		constexpr Translation& operator =(const Translation&) = default;

		constexpr bool operator ==(const Translation&) const = default;

		constexpr const VectorType& translation() const noexcept
		{
			return m_Translation;
		}

		constexpr VectorType& translation() noexcept
		{
			return m_Translation;
		}

	public:
		constexpr VectorType transform(VectorType vec) const noexcept
		{
			return vec += m_Translation;
		}

	private:
		TVectorType m_Translation{};
	};
}

#endif
