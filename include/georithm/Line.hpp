
//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_LINE_HPP
#define GEORITHM_LINE_HPP

#pragma once

#include <cassert>

#include "Defines.hpp"
#include "Concepts.hpp"

namespace georithm
{
	template<VectorObject TVectorType, LineType LType>
	class BasicLine
	{
	public:
		using VectorType = TVectorType;
		constexpr static LineType Type{ LType };

		constexpr BasicLine() noexcept = default;

		constexpr BasicLine(const VectorType& location, const VectorType& direction) noexcept :
			m_Location{ location },
			m_Direction{ direction }
		{
		}

		constexpr BasicLine(const BasicLine&) noexcept = default;
		constexpr BasicLine& operator =(const BasicLine&) noexcept = default;

		constexpr bool operator ==(const BasicLine& other) const noexcept = default;

		constexpr const VectorType& location() const noexcept
		{
			return m_Location;
		}

		constexpr VectorType& location() noexcept
		{
			return m_Location;
		}

		constexpr const VectorType& direction() const noexcept
		{
			return m_Direction;
		}

		constexpr VectorType& direction() noexcept
		{
			return m_Direction;
		}

		constexpr VectorType firstVertex() const noexcept
		{
			return m_Location;
		}

		constexpr VectorType secondVertex() const noexcept
		{
			return m_Location + m_Direction;
		}

		constexpr bool isNull() const noexcept
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
