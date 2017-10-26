/*
The MIT License (MIT)
Copyright (c) 2017 Yehonatan Ballas
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef gs_GenericSerialization_h
#define gs_GenericSerialization_h

#include <type_traits>
#include <utility>

namespace gs
{
	// input trait
	template<typename T>
	struct is_input : std::false_type {};

	template<typename T>
	constexpr bool is_input_v = is_input<T>::value;

	// output trait
	template<typename T>
	struct is_output : std::false_type {};

	template<typename T>
	constexpr bool is_output_v = is_output<T>::value;


	// serialize variadic template
	template<typename Stream, typename T, typename ...Ts>
	void serialize(Stream& stream, T& value, Ts&... args)
	{
		serialize(stream, value);
		serialize(stream, args...);
	}
}

#endif//guard