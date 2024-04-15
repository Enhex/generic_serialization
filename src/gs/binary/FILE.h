#pragma once

#include <gs/traits.h>
#include <cstdio>
#include <utility>

namespace gs
{
	// distinguish input and output
	struct iFile : std::FILE {};
	struct oFile : std::FILE {};

	// input trait
	template<>
	struct is_input<iFile> : std::true_type {};

	// output trait
	template<>
	struct is_output<oFile> : std::true_type {};
}
