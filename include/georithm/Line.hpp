//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_LINE_HPP
#define GEORITHM_LINE_HPP

#pragma once

#include <compare>

#include "Defines.hpp"
#include "Concepts.hpp"

namespace georithm
{
	template <VectorObject TVectorType, LineType TLineType>
	class BasicLine
	{
	public:
		using VectorType = TVectorType;
		using ValueType = typename VectorType::ValueType;
		constexpr static LineType type{ TLineType };

		constexpr BasicLine() noexcept = default;
		/*ToDo: c++20
		constexpr */
		~BasicLine() noexcept = default;

		constexpr BasicLine(const VectorType& location, const VectorType& direction) noexcept :
			m_Location{ location },
			m_Direction{ direction }
		{
		}

		constexpr BasicLine(const BasicLine&) noexcept = default;
		constexpr BasicLine& operator =(const BasicLine&) noexcept = default;
		constexpr BasicLine(BasicLine&&) noexcept = default;
		constexpr BasicLine& operator =(BasicLine&&) noexcept = default;

		constexpr bool operator ==(const BasicLine& other) const noexcept = default;

		[[nodiscard]] constexpr const VectorType& location() const noexcept
		{
			return m_Location;
		}

		[[nodiscard]] constexpr VectorType& location() noexcept
		{
			return m_Location;
		}

		[[nodiscard]] constexpr const VectorType& direction() const noexcept
		{
			return m_Direction;
		}

		[[nodiscard]] constexpr VectorType& direction() noexcept
		{
			return m_Direction;
		}

		[[nodiscard]] constexpr VectorType firstVertex() const noexcept
		{
			return m_Location;
		}

		[[nodiscard]] constexpr VectorType secondVertex() const noexcept
		{
			return m_Location + m_Direction;
		}

		[[nodiscard]] constexpr bool isNull() const noexcept
		{
			return m_Direction == VectorType::zero();
		}

	private:
		VectorType m_Location{};
		VectorType m_Direction{};
	};

	template <VectorObject TVectorType>
	using Line = BasicLine<TVectorType, LineType::line>;
	template <VectorObject TVectorType>
	using Ray = BasicLine<TVectorType, LineType::ray>;
	template <VectorObject TVectorType>
	using Segment = BasicLine<TVectorType, LineType::segment>;
}

#endif
