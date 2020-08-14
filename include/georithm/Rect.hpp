//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_RECT_HPP
#define GEORITHM_RECT_HPP

#pragma once

#include <cassert>
#include <type_traits>

#include "Concepts.hpp"
#include "Defines.hpp"
#include "Line.hpp"

namespace georithm::detail
{
	template <class T>
	struct ConditionalInherit :
		public T
	{
		template <class... TArgs>
		constexpr explicit ConditionalInherit(TArgs&&... args) noexcept :
			T{ std::forward<TArgs>(args)... }
		{
		}

		// Todo: c++20
		/*constexpr */~ConditionalInherit() noexcept = default;

		constexpr ConditionalInherit(const ConditionalInherit&) noexcept = default;
		constexpr ConditionalInherit& operator =(const ConditionalInherit&) noexcept = default;

		constexpr ConditionalInherit(ConditionalInherit&&) noexcept = default;
		constexpr ConditionalInherit& operator =(ConditionalInherit&&) noexcept = default;
		
		[[nodiscard]] constexpr auto operator <=>(const ConditionalInherit&) const noexcept = default;
	};

	template <>
	struct ConditionalInherit<void>
	{
		constexpr ConditionalInherit() noexcept = default;
		
		// Todo: c++20
		/*constexpr */~ConditionalInherit() noexcept = default;

		constexpr ConditionalInherit(const ConditionalInherit&) noexcept = default;
		constexpr ConditionalInherit& operator =(const ConditionalInherit&) noexcept = default;

		constexpr ConditionalInherit(ConditionalInherit&&) noexcept = default;
		constexpr ConditionalInherit& operator =(ConditionalInherit&&) noexcept = default;
		
		[[nodiscard]] constexpr auto operator <=>(const ConditionalInherit&) const noexcept = default;
	};
}

namespace georithm
{
	template <ValueType T, class TTransformer>
	class Rect :
		public detail::ConditionalInherit<TTransformer>
	{
	public:
		using VectorType = Vector<T, 2>;

		constexpr Rect() noexcept = default;
		/*ToDo: c++20
		constexpr */
		~Rect() noexcept = default;

		constexpr explicit Rect(const VectorType& span) noexcept :
			m_Span{ span }
		{
		}

		constexpr Rect(const VectorType& position, const VectorType& span) noexcept :
			m_Position{ position},
			m_Span{ span }
		{
		}

		constexpr Rect(const Rect&) noexcept = default;
		constexpr Rect& operator =(const Rect&) noexcept = default;
		constexpr Rect(Rect&&) noexcept = default;
		constexpr Rect& operator =(Rect&&) noexcept = default;

		//[[nodiscard]] constexpr bool operator ==(const Rect& other) const noexcept = default;

		template <class TTransformer2>
		[[nodiscard]] constexpr bool operator ==(const Rect<T, TTransformer2>& other) const noexcept
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
			return vertex + m_Position;
		}

		[[nodiscard]] constexpr Segment<VectorType> edge(EdgeIndex_t index) const noexcept
		{
			assert(0u <= index && index < edgeCount() && !isNull());

			auto first = vertex(index);
			auto second = vertex((index + 1) % vertexCount());
			return { first, second - first };
		}

		[[nodiscard]] constexpr const VectorType& position() const noexcept
		{
			return m_Position;
		}

		[[nodiscard]] constexpr VectorType& position() noexcept
		{
			return m_Position;
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
		VectorType m_Position;
		VectorType m_Span;
	};

	template <ValueType T>
	using AABB_t = Rect<T, void>;
}

#endif
