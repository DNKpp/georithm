//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_RANGE_ALGORITHMS_HPP
#define GEORITHM_RANGE_ALGORITHMS_HPP

#pragma once

#include <type_traits>
#include <iterator>

#include "Concepts.hpp"

namespace georithm::detail
{
	template <class Fn, class ForwardIt, class InputIt>
	concept ZipElementsInvocable = invocable_r<Fn, typename std::iterator_traits<ForwardIt>::value_type, typename std::iterator_traits<ForwardIt>::value_type,
												typename std::iterator_traits<InputIt>::value_type>;
}

namespace georithm
{
	template <std::forward_iterator ForwardIt, std::sentinel_for<ForwardIt> ForwardItSentinel, std::input_iterator
		InputIt, detail::ZipElementsInvocable<ForwardIt, InputIt> BinaryOp>
	constexpr void zip_elements(ForwardIt first, ForwardItSentinel last, InputIt secFirst, BinaryOp op)
	noexcept(std::is_nothrow_invocable_v<BinaryOp, typename std::iterator_traits<ForwardIt>::value_type, typename std::iterator_traits<InputIt>::value_type>)
	{
		while (first != last)
		{
			// ToDo: *first = std::invoke(op, *first, *secFirst);
			*first = op(*first, *secFirst);
			++first;
			++secFirst;
		}
	}
}

#endif
