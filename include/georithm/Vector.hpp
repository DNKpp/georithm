
//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_VECTOR_HPP
#define GEORITHM_VECTOR_HPP

#pragma once

#include <array>
#include <algorithm>
#include <numeric>
#include <cassert>

#include "Concepts.hpp"
#include "RangeAlgorithms.hpp"
#include "ArithmeticOperators.hpp"

namespace georithm
{
	template<ValueType T, DimensionDescriptor_t Dim>
	requires Cardinality<Dim>
	class Vector :
		private Arithmetic<Vector<T, Dim>>
	{
	public:
		using ValueType = T;
		using DimensionDescriptorType = decltype(Dim);
		constexpr static DimensionDescriptorType Dimensions{ Dim };

		constexpr Vector() noexcept = default;
		constexpr Vector(const Vector&) noexcept = default;
		constexpr Vector& operator =(const Vector&) noexcept = default;

		template <class... Args>
		requires (sizeof...(Args) == Dim) && std::convertible_to<std::common_type_t<Args...>, T>
		constexpr Vector(Args&&... args) noexcept :
			m_Values{ std::forward<Args>(args)... }
		{
		}

		constexpr static Vector zero() noexcept
		{
			return make(T(0));
		}

		constexpr const ValueType& operator [](DimensionDescriptorType index) const noexcept
		{
			return m_Values[index];
		}

		constexpr ValueType& operator [](DimensionDescriptorType index) noexcept
		{
			return m_Values[index];
		}

		template <DimensionDescriptor_t Dim2 = Dim>
		requires (1 <= Dim2)
		constexpr const ValueType& x() const noexcept
		{
			return m_Values[0];
		}

		template <DimensionDescriptor_t Dim2 = Dim>
		requires (1 <= Dim2)
		constexpr ValueType& x() noexcept
		{
			return m_Values[0];
		}

		template <DimensionDescriptor_t Dim2 = Dim>
		requires (2 <= Dim2)
		constexpr const ValueType& y() const noexcept
		{
			return m_Values[1];
		}

		template <DimensionDescriptor_t Dim2 = Dim>
		requires (2 <= Dim2)
		constexpr ValueType& y() noexcept
		{
			return m_Values[1];
		}

		template <DimensionDescriptor_t Dim2 = Dim>
		requires (3 <= Dim2)
		constexpr const ValueType& z() const noexcept
		{
			return m_Values[2];
		}

		template <DimensionDescriptor_t Dim2 = Dim>
		requires (3 <= Dim2)
		constexpr ValueType& z() noexcept
		{
			return m_Values[2];
		}

		constexpr bool operator ==(const Vector& other) const noexcept = default;

		template <class U>
		requires Addable<T, U>
		constexpr Vector& operator +=(const Vector<U, Dim>& other) noexcept
		{
			zip_elements(std::begin(m_Values), std::end(m_Values), std::begin(other.m_Values),
				[](auto lhs, const auto& rhs) { return lhs += static_cast<T>(rhs); }
			);
			return *this;
		}

		template <class U>
		requires Subtractable<T, U>
		constexpr Vector& operator -=(const Vector<U, Dim>& other) noexcept
		{
			zip_elements(std::begin(m_Values), std::end(m_Values), std::begin(other.m_Values),
				[](auto lhs, const auto& rhs) { return lhs -= static_cast<T>(rhs); }
			);
			return *this;
		}

		template <class U>
		requires Addable<T, U>
		constexpr Vector& operator +=(const U& other) noexcept
		{
			std::for_each(std::begin(m_Values), std::end(m_Values),
				[&other](auto& lhs) { return lhs += static_cast<T>(other); }
			);
			return *this;
		}

		template <class U>
		requires Subtractable<T, U>
		constexpr Vector& operator -=(const U& other) noexcept
		{
			std::for_each(std::begin(m_Values), std::end(m_Values),
				[&other](auto& lhs) { return lhs -= static_cast<T>(other); }
			);
			return *this;
		}

		template <class U>
		requires Multiplicable<T, U>
		constexpr Vector& operator *=(const U& other) noexcept
		{
			std::for_each(std::begin(m_Values), std::end(m_Values),
				[&other](auto& lhs) { return lhs *= static_cast<T>(other); }
			);
			return *this;
		}

		template <class U>
		requires Divisable<T, U>
		constexpr Vector& operator /=(const U& other) noexcept
		{
			assert(other != U(0));
			std::for_each(std::begin(m_Values), std::end(m_Values),
				[&other](auto& lhs) { return lhs /= static_cast<T>(other); }
			);
			return *this;
		}

		template <class U>
		requires Moduloable<T, U>
		constexpr Vector& operator %=(const U& other) noexcept
		{
			assert(other != U(0));
			std::for_each(std::begin(m_Values), std::end(m_Values),
				[&other](auto& lhs) { return lhs %= other; }
			);
			return *this;
		}

		constexpr auto begin() noexcept
		{
			return std::begin(m_Values);
		}

		constexpr auto begin() const noexcept
		{
			return std::begin(m_Values);
		}

		constexpr auto cbegin() const noexcept
		{
			return std::cbegin(m_Values);
		}

		constexpr auto end() noexcept
		{
			return std::end(m_Values);
		}

		constexpr auto end() const noexcept
		{
			return std::end(m_Values);
		}

		constexpr auto cend() const noexcept
		{
			return std::cend(m_Values);
		}

		constexpr auto rbegin() noexcept
		{
			return std::rbegin(m_Values);
		}

		constexpr auto rbegin() const noexcept
		{
			return std::rbegin(m_Values);
		}

		constexpr auto crbegin() const noexcept
		{
			return std::crbegin(m_Values);
		}

		constexpr auto rend() noexcept
		{
			return std::rend(m_Values);
		}

		constexpr auto rend() const noexcept
		{
			return std::rend(m_Values);
		}

		constexpr auto crend() const noexcept
		{
			return std::crend(m_Values);
		}

	private:
		std::array<T, Dimensions> m_Values{};

		constexpr static Vector make(const T& value) noexcept
		{
			Vector tmp;
			tmp.m_Values.fill(value);
			return tmp;
		}
	};

	template <class T, class... U>
	Vector(T, U...) -> Vector<T, 1 + sizeof...(U)>;

	template <VectorObject TVector>
	requires ConstForwardIteratable<TVector>
	constexpr typename TVector::ValueType lengthSq(const TVector& vector) noexcept
	{
		return std::accumulate(std::cbegin(vector), std::cend(vector), typename TVector::ValueType(0),
			[](auto value, const auto& element) { return value + element * element; }
		);
	}

	template <VectorObject TVector1, VectorObject TVector2>
	requires ConstForwardIteratable<TVector1> && ConstForwardIteratable<TVector2> &&
		(TVector1::Dimensions == TVector2::Dimensions) &&
		Multiplicable<typename TVector1::ValueType, typename TVector2::ValueType>
	constexpr typename TVector1::ValueType scalarProduct(const TVector1& lhs, const TVector2& rhs) noexcept
	{
		return std::inner_product(std::cbegin(lhs), std::cend(lhs), std::cbegin(rhs), typename TVector1::ValueType(0));
	}

	template <VectorObject TVector>
	constexpr typename TVector::ValueType length(const TVector& vector) noexcept
	{
		return static_cast<TVector::ValueType>(std::sqrt(lengthSq(vector)));
	}

	template <class U, VectorObject TVector>
	constexpr U length(const TVector& vector) noexcept
	{
		return static_cast<U>(std::sqrt(lengthSq(vector)));
	}
}

#endif
