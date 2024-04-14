#pragma once

#include <type_traits>
#include <utility>

namespace gs
{
	// input trait
	template<typename T>
	struct is_input : std::false_type {};

	template<typename T>
	constexpr bool is_input_v = is_input<std::decay_t<T>>::value;

	// output trait
	template<typename T>
	struct is_output : std::false_type {};

	template<typename T>
	constexpr bool is_output_v = is_output<std::decay_t<T>>::value;
}
