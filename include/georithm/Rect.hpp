
//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_RECT_HPP
#define GEORITHM_RECT_HPP

#pragma once

#include <cassert>

#include "Concepts.hpp"
#include "Defines.hpp"
#include "Line.hpp"

namespace georithm
{
	template<class TVectorType, class... TTransformComponent>
	requires (TransformComponent<TTransformComponent, TVectorType> && ...)
	class Rect :
		public TTransformComponent...
	{
	public:
		using VectorType = TVectorType;

		constexpr Rect() noexcept = default;
		
		template <class... Args>
		constexpr Rect(const VectorType& span, Args&&... args) noexcept :
			m_Span{ span },
			TTransformComponent{ std::forward<Args>(args) }...
		{
		}

		constexpr Rect(const Rect&) noexcept = default;
		constexpr Rect& operator =(const Rect&) noexcept = default;

		constexpr bool operator ==(const Rect& other) const noexcept = default;

		constexpr VertexIndex_t vertexCount() const noexcept
		{
			return 4u;
		}

		constexpr VertexIndex_t edgeCount() const noexcept
		{
			return 4u;
		}

		constexpr VectorType vertex(VertexIndex_t index) const noexcept
		{
			assert(0u <= index && index < vertexCount() && !isNull());

			auto vertex = VectorType::zero();
			vertex.x() = (index == 1 || index == 2) ? m_Span.x() : vertex.x();
			vertex.y() = (index == 2 || index == 3) ? m_Span.y() : vertex.y();
			((vertex = static_cast<const TTransformComponent&>(*this).transform(vertex)), ...);
			return vertex;
		}

		constexpr Segment<VectorType> edge(EdgeIndex_t index) const noexcept
		{
			assert(0u <= index && index < edgeCount() && !isNull());

			auto first = vertex(index);
			auto second = vertex((index + 1) % vertexCount());
			return { first, second - first };
		}

		constexpr const VectorType& span() const noexcept
		{
			return m_Span;
		}

		constexpr VectorType& span() noexcept
		{
			return m_Span;
		}

		constexpr bool isNull() const noexcept
		{
			return m_Span.x() == 0 || m_Span.y() == 0;
		}

	private:
		VectorType m_Span{};
	};
}

#endif
