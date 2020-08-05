
//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_CONCEPTS_HPP
#define GEORITHM_CONCEPTS_HPP

#pragma once

#include <concepts>
#include <cstdint>
#include <iterator>
#include <type_traits>
#include <utility>

#include "Defines.hpp"
#include "GeometricTraits.hpp"

namespace georithm
{
	template <class T, class U = T>
	concept AddAssignable = requires (T lhs, U rhs)
	{
		{ lhs += rhs };
	};

	template <class T, class U = T>
	concept SubtractAssignable = requires (T lhs, U rhs)
	{
		{ lhs -= rhs };
	};

	template <class T, class U = T>
	concept MultiplyAssignable = requires (T lhs, U rhs)
	{
		{ lhs *= rhs };
	};

	template <class T, class U = T>
	concept DivideAssignable = requires (T lhs, U rhs)
	{
		{ lhs /= rhs };
	};

	template <class T, class U = T>
	concept ModuloAssignable = requires (T lhs, U rhs)
	{
		{ lhs %= rhs };
	};

	template <class T, class U = T>
	concept Addable = AddAssignable<T, U> && requires (T lhs, U rhs)
	{
		{ lhs + rhs }->std::convertible_to<T>;
	};

	template <class T, class U = T>
	concept Subtractable = SubtractAssignable<T, U> && requires (T lhs, U rhs)
	{
		{ lhs - rhs } -> std::convertible_to<T>;
	};

	template <class T, class U = T>
	concept Multiplicable = MultiplyAssignable<T, U> && requires (T lhs, U rhs)
	{
		{ lhs* rhs } -> std::convertible_to<T>;
	};

	template <class T, class U = T>
	concept Divisable = DivideAssignable<T, U> && requires (T lhs, U rhs)
	{
		{ lhs / rhs } -> std::convertible_to<T>;
	};

	template <class T, class U = T>
	concept Moduloable = ModuloAssignable<T, U> && requires (T lhs, U rhs)
	{
		{ lhs% rhs }->std::convertible_to<T>;
	};

	template <class TGeo1, class TGeo2>
	concept EqualDimensions = (GeometricTraits<TGeo1>::Dimensions == GeometricTraits<TGeo2>::Dimensions);

	template <class T>
	concept ForwardIteratable = requires (std::remove_cvref_t<T> & object)
	{
		{ std::begin(object) }->std::forward_iterator;
		{ object.end() }->std::sentinel_for<decltype(std::begin(object))>;
	};

	template <class T>
	concept ConstForwardIteratable = requires (const std::remove_cvref_t<T> & object)
	{
		{ std::begin(object) }->std::forward_iterator;
		{ object.cbegin() }->std::forward_iterator;
		{ object.end() }->std::sentinel_for<decltype(std::cbegin(object))>;
		{ object.cend() }->std::sentinel_for<decltype(std::cbegin(object))>;
	};

	template <class T>
	concept BiDirectionalIteratable = ForwardIteratable<T> && requires (std::remove_cvref_t<T> & object)
	{
		{ object.rbegin() }->std::bidirectional_iterator;
		{ object.rend() }->std::sentinel_for<decltype(std::rbegin(object))>;
	};

	template <class T>
	concept ConstBiDirectionalIteratable = ConstForwardIteratable<T> && requires (const std::remove_cvref_t<T> & object)
	{
		{ object.rbegin() }->std::bidirectional_iterator;
		{ object.crbegin() }->std::bidirectional_iterator;
		{ object.rend() }->std::sentinel_for<decltype(std::crbegin(object))>;
		{ object.crend() }->std::sentinel_for<decltype(std::crbegin(object))>;
	};

	template <class T>
	concept ValueType = Addable<T> && Subtractable<T> && Multiplicable<T> && Divisable<T> && std::equality_comparable<T>;

	template <auto Value>
	concept Cardinality = std::convertible_to<decltype(Value), DimensionDescriptor_t> && (Value > 0);

	template <class T>
	concept VectorObject = requires (const std::remove_cvref_t<T> & vec)
	{
		{ T::ValueType };
		{ T::Dimensions }->std::convertible_to<DimensionDescriptor_t>;
		{ vec[std::declval<DimensionDescriptor_t>()] }->std::convertible_to<typename T::ValueType>;
	};

	template <class T, DimensionDescriptor_t Dim>
	concept NDimensionalVectorObject = VectorObject<T> && (T::Dimensions == Dim);

	template<class Fn, class R, class... Args>
	concept invocable_r = std::is_invocable_r_v<R, Fn, Args...>;

	template <class T, class ExpectedVectorType>
	concept TransformComponent = requires (const std::remove_cvref_t<T> & component)
	{
		{ T::VectorType };
		{ component.transform(std::declval<ExpectedVectorType>()) }->std::convertible_to<ExpectedVectorType>;
	};

	template <class T>
	concept GeometricObject = requires (const std::remove_cvref_t<T> & object)
	{
		{ T::VectorType };
		{ isNull(object) }->std::convertible_to<bool>;
	};

	template <class T, DimensionDescriptor_t Dim>
	concept NDimensionalObject = GeometricObject<T> && (T::VectorType::Dimensions == Dim);

	template <class T>
	concept LineObject = GeometricObject<T> && requires(const std::remove_cvref_t<T> & line)
	{
		{ T::Type };
		{ line.firstVertex() }->std::convertible_to<typename T::VectorType>;
		{ line.secondVertex() }->std::convertible_to<typename T::VectorType>;
	};

	template <class T, DimensionDescriptor_t Dim>
	concept NDimensionalLineObject = NDimensionalObject<T, Dim> && LineObject<T>;

	template <class T>
	concept PolygonalObject = GeometricObject<T> && requires (const std::remove_cvref_t<T> & object)
	{
		{ object.vertexCount() } -> std::convertible_to<VertexIndex_t>;
		{ object.edgeCount() } -> std::convertible_to<EdgeIndex_t>;
		{ object.vertex(std::declval<VertexIndex_t>()) }->VectorObject;
		{ object.edge(std::declval<VertexIndex_t>()) }->LineObject;
	};

	template <class T, DimensionDescriptor_t Dim>
	concept NDimensionalPolygonalObject = NDimensionalObject<T, Dim> && PolygonalObject<T>;

	//template <class T>
	//concept Circular = GeometricObject && requires (T object)
	//{
	//	{ object.radius() }->std::convertible_to<T::VectorType>;
	//};
}

#endif
