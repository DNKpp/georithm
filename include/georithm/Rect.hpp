//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_RECT_HPP
#define GEORITHM_RECT_HPP

#pragma once

#include <cassert>
#include <compare>

#include "Concepts.hpp"
#include "Defines.hpp"
#include "Line.hpp"

namespace georithm
{
	template <class TVectorType, class... TTransformComponent>
	requires (TransformComponent<TTransformComponent, TVectorType> && ...)
	class Rect :
		public TTransformComponent...
	{
	public:
		using VectorType = TVectorType;

		constexpr Rect() noexcept = default;
		/*ToDo: c++20
		constexpr */
		~Rect() noexcept = default;

		template <class... TArgs>
		constexpr Rect(const VectorType& span, TArgs&&... args) noexcept :
			TTransformComponent{ std::forward<TArgs>(args) }...,
			m_Span{ span }
		{
		}

		constexpr Rect(const Rect&) noexcept = default;
		constexpr Rect& operator =(const Rect&) noexcept = default;
		constexpr Rect(Rect&&) noexcept = default;
		constexpr Rect& operator =(Rect&&) noexcept = default;

		constexpr bool operator ==(const Rect& other) const noexcept = default;

		template <class... T2TransformComponents>
		constexpr bool operator ==(const Rect<TVectorType, T2TransformComponents...>& other) const noexcept
		{
			for (VertexIndex_t i = 0; i < vertexCount(); ++i)
			{
				if (vertex(i) != other.vertex(i))
					return false;
			}
			return true;
		}

		[[nodiscard]] constexpr VertexIndex_t vertexCount() const noexcept
		{
			return 4u;
		}

		[[nodiscard]] constexpr VertexIndex_t edgeCount() const noexcept
		{
			return 4u;
		}

		[[nodiscard]] constexpr VectorType vertex(VertexIndex_t index) const noexcept
		{
			assert(0u <= index && index < vertexCount() && !isNull());

			auto vertex = VectorType::zero();
			vertex.x() = index == 1 || index == 2 ? m_Span.x() : vertex.x();
			vertex.y() = index == 2 || index == 3 ? m_Span.y() : vertex.y();
			((vertex = static_cast<const TTransformComponent&>(*this).transform(vertex)), ...);
			return vertex;
		}

		[[nodiscard]] constexpr Segment<VectorType> edge(EdgeIndex_t index) const noexcept
		{
			assert(0u <= index && index < edgeCount() && !isNull());

			auto first = vertex(index);
			auto second = vertex((index + 1) % vertexCount());
			return { first, second - first };
		}

		[[nodiscard]] constexpr const VectorType& span() const noexcept
		{
			return m_Span;
		}

		[[nodiscard]] constexpr VectorType& span() noexcept
		{
			return m_Span;
		}

		[[nodiscard]] constexpr bool isNull() const noexcept
		{
			return m_Span == VectorType::zero();
		}

	private:
		VectorType m_Span{};
	};
}

#endif
