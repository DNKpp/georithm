
//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_RANGE_ALGORITHMS_HPP
#define GEORITHM_RANGE_ALGORITHMS_HPP

#pragma once

#include <concepts>
#include <iterator>

namespace georithm
{
	template <std::forward_iterator ForwardIt, std::sentinel_for<ForwardIt> ForwardItSentinel, std::input_iterator InputIt,
		invocable_r<typename std::iterator_traits<ForwardIt>::value_type, typename std::iterator_traits<ForwardIt>::value_type, typename std::iterator_traits<InputIt>::value_type> BinaryOp>
	constexpr void zip_elements(ForwardIt first, ForwardItSentinel last, InputIt secFirst, BinaryOp op)
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
