#pragma once

#include <gs/traits.h>
#include <fstream>

namespace gs
{
	// input trait
	template<>
	struct is_input<std::ifstream> : std::true_type {};

	// output trait
	template<>
	struct is_output<std::ofstream> : std::true_type {};
}
