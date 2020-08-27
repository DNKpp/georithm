//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_CONCEPTS_HPP
#define GEORITHM_CONCEPTS_HPP

#pragma once

#include <concepts>
#include <type_traits>

#include "georithm/BasicConcepts.hpp"
#include "georithm/Defines.hpp"
#include "georithm/GeometricTraits.hpp"

namespace georithm
{
	template <class TGeo1, class TGeo2>
	concept EqualDimensions = GeometricTraits<TGeo1>::dimensions == GeometricTraits<TGeo2>::dimensions;

	template <class T>
	concept ValueType = Addable<T> && Subtractable<T> && Multiplicable<T> && Divisable<T> && std::equality_comparable<T>
	;

	template <auto TValue>
	concept Cardinality = implicit_convertible_to<decltype(TValue), DimensionDescriptor_t> && TValue > 0;

	template <class T>
	concept VectorObject = requires(const std::remove_cvref_t<T>& vec)
	{
		typename T::ValueType;
		{ T::dimensions } -> implicit_convertible_to<DimensionDescriptor_t>;
		{ vec[std::declval<DimensionDescriptor_t>()] } -> implicit_convertible_to<typename T::ValueType>;
	};

	template <class T, DimensionDescriptor_t TDim>
	concept NDimensionalVectorObject = VectorObject<T> && T::dimensions == TDim;

	template <class T, class TExpectedVectorType>
	concept TransformComponent = std::default_initializable<T> && requires(const std::remove_cvref_t<T>& component)
	{
		typename T::ValueType;
		typename T::VectorType;
		{ component.transform(std::declval<TExpectedVectorType>()) } -> implicit_convertible_to<TExpectedVectorType>;
	};

	template <class T>
	concept GeometricObject = requires(const std::remove_cvref_t<T>& object)
	{
		typename GeometricTraits<T>::ValueType;
		typename GeometricTraits<T>::VectorType;
		{ GeometricTraits<T>::dimensions };
		{ isNull(object) } -> implicit_convertible_to<bool>;
	};

	template <class T, DimensionDescriptor_t TDim>
	concept NDimensionalObject = GeometricObject<T> && GeometricTraits<T>::dimensions == TDim;

	template <class T>
	concept LineObject = GeometricObject<T> && requires(const std::remove_cvref_t<T>& line)
	{
		{ T::type };
		{ line.firstVertex() } -> implicit_convertible_to<typename T::VectorType>;
		{ line.secondVertex() } -> implicit_convertible_to<typename T::VectorType>;
	};

	template <class T, DimensionDescriptor_t TDim>
	concept NDimensionalLineObject = NDimensionalObject<T, TDim> && LineObject<T>;

	template <class T>
	concept PolygonalObject = GeometricObject<T> && requires(const std::remove_cvref_t<T>& object)
	{
		{ vertexCount(object) } -> implicit_convertible_to<VertexIndex_t>;
		{ edgeCount(object) } -> implicit_convertible_to<EdgeIndex_t>;
		{ vertex(object, std::declval<VertexIndex_t>()) } -> VectorObject;
		{ edge(object, std::declval<VertexIndex_t>()) } -> LineObject;
	};

	template <class T, DimensionDescriptor_t TDim>
	concept NDimensionalPolygonalObject = NDimensionalObject<T, TDim> && PolygonalObject<T>;

	//template <class T>
	//concept Circular = GeometricObject && requires (T object)
	//{
	//	{ object.radius() }->std::convertible_to<T::VectorType>;
	//};
}

#endif
