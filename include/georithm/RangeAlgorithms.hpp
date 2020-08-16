//          Copyright Dominic Koepke 2017 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GEORITHM_RANGE_ALGORITHMS_HPP
#define GEORITHM_RANGE_ALGORITHMS_HPP

#pragma once

#include <iterator>
#include <type_traits>

#include "Concepts.hpp"

namespace georithm::detail
{
	template <class TFn, class TForwardIt, class TInputIt>
	concept ZipElementsInvocable = invocable_r<TFn,
												typename std::iterator_traits<TForwardIt>::value_type,
												typename std::iterator_traits<TForwardIt>::value_type,
												typename std::iterator_traits<TInputIt>::value_type>;
}

namespace georithm
{
	template <std::forward_iterator TForwardIt, std::sentinel_for<TForwardIt> ForwardItSentinel, std::input_iterator TInputIt, detail::ZipElementsInvocable<
		TForwardIt, TInputIt> TBinaryOp>
	constexpr void zip_elements(TForwardIt first,
								ForwardItSentinel last,
								TInputIt secFirst,
								TBinaryOp op
	)
	noexcept(std::is_nothrow_invocable_v<TBinaryOp, typename std::iterator_traits<TForwardIt>::value_type, typename std::iterator_traits<TInputIt>::value_type>)
	{
		while (first != last)
		{
			//*first = std::invoke(op, *first, *secFirst);
			*first = op(*first, *secFirst);
			++first;
			++secFirst;
		}
	}
}

#endif
