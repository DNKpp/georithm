//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_TRANSFORM_ROTATE_HPP
#define GEORITHM_TRANSFORM_ROTATE_HPP

#pragma once

#include "georithm/Concepts.hpp"
#include "georithm/Vector.hpp"

namespace georithm::transform::detail
{
	template <class T1, class T2, bool TResult>
	struct ConditionalType
	{
		using Type = T2;
	};

	template <class T1, class T2>
	struct ConditionalType<T1, T2, true>
	{
		using Type = T1;
	};

	template <class T1, class T2, bool TResult>
	using ConditionalType_t = typename ConditionalType<T1, T2, TResult>::Type;
}

namespace georithm::transform
{
	template <VectorObject TVectorType, class TArcType = detail::ConditionalType_t<
		typename TVectorType::ValueType,
		double, std::is_floating_point_v<typename TVectorType::ValueType>>>
	class Rotate
	{
	public:
		using VectorType = TVectorType;
		using ValueType = TArcType;

		constexpr Rotate() noexcept = default;
		/*ToDo: c++20
		constexpr */
		~Rotate() noexcept = default;

		constexpr explicit Rotate(const ValueType& rotation) noexcept :
			m_Rotation{ rotation }
		{
		}

		constexpr Rotate(const Rotate&) = default;
		constexpr Rotate& operator =(const Rotate&) = default;
		constexpr Rotate(Rotate&&) = default;
		constexpr Rotate& operator =(Rotate&&) = default;

		[[nodiscard]] constexpr bool operator ==(const Rotate&) const = default;

		[[nodiscard]] constexpr const ValueType& rotation() const noexcept
		{
			return m_Rotation;
		}

		[[nodiscard]] constexpr ValueType& rotation() noexcept
		{
			return m_Rotation;
		}

		[[nodiscard]] constexpr VectorType transform(VectorType vec) const noexcept
		{
			return rotate(vec, m_Rotation);
		}

	private:
		ValueType m_Rotation{};
	};
}

#endif
