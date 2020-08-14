//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_VECTOR_HPP
#define GEORITHM_VECTOR_HPP

#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <concepts>
#include <numeric>

#include "ArithmeticOperators.hpp"
#include "Concepts.hpp"
#include "RangeAlgorithms.hpp"

namespace georithm
{
	template <ValueType T, DimensionDescriptor_t Dim>
	requires Cardinality<Dim>
	class Vector :
		private Arithmetic
	{
	public:
		using ValueType = T;
		using DimensionDescriptorType = DimensionDescriptor_t;
		constexpr static DimensionDescriptorType Dimensions{ Dim };

		constexpr Vector() noexcept = default;
		/*ToDo: c++20
		constexpr */
		~Vector() noexcept = default;

		constexpr Vector(const Vector&) noexcept = default;
		constexpr Vector& operator =(const Vector&) noexcept = default;

		constexpr Vector(Vector&&) noexcept = default;
		constexpr Vector& operator =(Vector&&) noexcept = default;

		template <class... TArgs>
		requires (sizeof...(TArgs) == Dim) && std::is_same_v<std::common_type_t<TArgs...>, T>
		constexpr Vector(TArgs&&... args) noexcept :
			m_Values{ std::forward<TArgs>(args)... }
		{
		}

		template <class T2>
		requires (!std::is_same_v<T2, T> && std::convertible_to<T2, T>)
		explicit constexpr Vector(const Vector<T2, Dim>& other) noexcept
		{
			std::transform(std::begin(other), std::end(other), std::begin(m_Values),
							[](T2 value) -> T { return static_cast<T>(value); }
						);
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
		[[nodiscard]] constexpr const ValueType& x() const noexcept
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
		[[nodiscard]] constexpr const ValueType& y() const noexcept
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
		[[nodiscard]] constexpr const ValueType& z() const noexcept
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

		template <class T2>
		requires Addable<T, T2>
		constexpr Vector& operator +=(const Vector<T2, Dim>& other) noexcept
		{
			zip_elements(std::begin(m_Values), std::end(m_Values), std::begin(other.m_Values),
						[](auto lhs, const auto& rhs) { return lhs += static_cast<T>(rhs); }
						);
			return *this;
		}

		template <class T2>
		requires Subtractable<T, T2>
		constexpr Vector& operator -=(const Vector<T2, Dim>& other) noexcept
		{
			zip_elements(std::begin(m_Values), std::end(m_Values), std::begin(other.m_Values),
						[](auto lhs, const auto& rhs) { return lhs -= static_cast<T>(rhs); }
						);
			return *this;
		}

		template <class T2>
		requires Addable<T, T2>
		constexpr Vector& operator +=(const T2& other) noexcept
		{
			std::for_each(std::begin(m_Values), std::end(m_Values),
						[&other](auto& lhs) { return lhs += static_cast<T>(other); }
						);
			return *this;
		}

		template <class T2>
		requires Subtractable<T, T2>
		constexpr Vector& operator -=(const T2& other) noexcept
		{
			std::for_each(std::begin(m_Values), std::end(m_Values),
						[&other](auto& lhs) { return lhs -= static_cast<T>(other); }
						);
			return *this;
		}

		template <class T2>
		requires Multiplicable<T, T2>
		constexpr Vector& operator *=(const T2& other) noexcept
		{
			std::for_each(std::begin(m_Values), std::end(m_Values),
						[&other](auto& lhs) { return lhs *= static_cast<T>(other); }
						);
			return *this;
		}

		template <class T2>
		requires Multiplicable<T2, T>
		friend Vector operator *(const T2& lhs, Vector rhs) noexcept
		{
			std::for_each(std::begin(rhs), std::end(rhs),
						[&lhs](auto& el) { return el *= static_cast<T>(lhs); }
						);
			return rhs;
		}

		template <class T2>
		requires Divisable<T, T2>
		constexpr Vector& operator /=(const T2& other) noexcept
		{
			assert(other != T2(0));
			std::for_each(std::begin(m_Values), std::end(m_Values),
						[&other](auto& lhs) { return lhs /= static_cast<T>(other); }
						);
			return *this;
		}

		template <class T2>
		requires Moduloable<T, T2>
		constexpr Vector& operator %=(const T2& other) noexcept
		{
			assert(other != T2(0));
			std::for_each(std::begin(m_Values), std::end(m_Values),
						[&other](auto& lhs) { return lhs %= other; }
						);
			return *this;
		}

		[[nodiscard]] constexpr auto begin() noexcept
		{
			return std::begin(m_Values);
		}

		[[nodiscard]] constexpr auto begin() const noexcept
		{
			return std::begin(m_Values);
		}

		[[nodiscard]] constexpr auto cbegin() const noexcept
		{
			return std::cbegin(m_Values);
		}

		constexpr auto end() noexcept
		{
			return std::end(m_Values);
		}

		[[nodiscard]] constexpr auto end() const noexcept
		{
			return std::end(m_Values);
		}

		[[nodiscard]] constexpr auto cend() const noexcept
		{
			return std::cend(m_Values);
		}

		constexpr auto rbegin() noexcept
		{
			return std::rbegin(m_Values);
		}

		[[nodiscard]] constexpr auto rbegin() const noexcept
		{
			return std::rbegin(m_Values);
		}

		[[nodiscard]] constexpr auto crbegin() const noexcept
		{
			return std::crbegin(m_Values);
		}

		constexpr auto rend() noexcept
		{
			return std::rend(m_Values);
		}

		[[nodiscard]] constexpr auto rend() const noexcept
		{
			return std::rend(m_Values);
		}

		[[nodiscard]] constexpr auto crend() const noexcept
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
	Vector(T, U ...) -> Vector<T, 1 + sizeof...(U)>;

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
		return static_cast<typename TVector::ValueType>(std::sqrt(lengthSq(vector)));
	}

	template <class T2, VectorObject TVector>
	constexpr T2 length(const TVector& vector) noexcept
	{
		return static_cast<T2>(std::sqrt(lengthSq(vector)));
	}

	template <VectorObject TVector>
	requires std::floating_point<typename TVector::ValueType>
	constexpr TVector normalize(TVector vector) noexcept
	{
		assert(vector != TVector::zero());

		auto length = georithm::length(vector);
		return vector /= length;
	}

	template <VectorObject TVector>
	requires std::floating_point<typename TVector::ValueType> || std::signed_integral<typename TVector::ValueType>
	constexpr TVector abs(TVector vector) noexcept
	{
		for (auto& el : vector)
			el = std::abs(el);
		return vector;
	}
}

#endif
